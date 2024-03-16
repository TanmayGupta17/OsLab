#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<semaphore.h>
#include<unistd.h>
#include<pthread.h>

sem_t rmutex, wmutex;
int data = 0;
int rcount = 0;

void *reade(void *arg){
  int f= ((int) arg);
  sem_wait(&rmutex);
  rcount = rcount+1;
  if(rcount == 1) sem_wait(&wmutex);
  sem_post(&rmutex);
  printf("Data read by reader%d: %d\n",f,data);
  sleep(1);
  
  sem_wait(&rmutex);
  rcount = rcount - 1;
  if(rcount == 0) sem_post(&wmutex);
  sem_post(&rmutex);
}

void *writee(void *arg){
  int f = ((int)arg);
  sem_wait(&wmutex);
  data++;
  printf("Data modified by writer%d: %d\n",f,data);
  sleep(1);
  sem_post(&wmutex);
}

int main(){
  int i;
  pthread_t writer[5],reader[5];
  sem_init(&rmutex,0,1);
  sem_init(&wmutex,0,1);
  
  for(int i=0;i<5;i++){
    pthread_create(&writer[i],NULL,writee,(void *)i);
    pthread_create(&reader[i],NULL,reade,(void *)i);
  }
  
  for(int i=0;i<5;i++){
    pthread_join(writer[i],NULL);
    pthread_join(reader[i],NULL);
  }
  return 0;
}
