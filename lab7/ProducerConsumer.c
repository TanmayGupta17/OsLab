#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<sys/wait.h>
#include<unistd.h>
#include<signal.h>
#include<pthread.h>

#define MAX_CAPACITY 100

int buff[MAX_CAPACITY];
sem_t pmutex,cmutex,empty,full;
int in = 1, out = 1;
int item = 0;

void *produce(void *args){
  sem_wait(&empty);
  item++;
  sem_wait(&pmutex);
  buff[in] = item;
  printf("Produced Data: %d",buff[in]);
  in = in % MAX_CAPACITY + 1;
  sem_post(&pmutex);
  sem_post(&full);
}

void *consume(void *args){
  int citem = 0;
  sem_wait(&full);
  sem_wait(&cmutex);
  citem = buff[out];
  printf("Consumed Data: %d",buff[out]);
  out = out % MAX_CAPACITY + 1;
  sem_post(&cmutex);
  sem_post(&empty);
}

int main(int argc, const char *argv[]){
  in = 1;
  out = 1;
  int i, NThreads;
  sem_init(&pmutex,0,1);
  sem_init(&cmutex,0,1);
  sem_init(&full,0,0);
  sem_init(&empty,0,MAX_CAPACITY);
  
  pthread_t *producers, *consumers;
  NThreads = abs(atoi(argv[1]));
  producers = (pthread_t *)malloc((sizeof(pthread_t)*NThreads));
  consumers = (pthread_t *)malloc((sizeof(pthread_t)*NThreads));
  
  for(int i=0;i<NThreads;i++){
    pthread_create(&producers[i],NULL,&produce,NULL);
    pthread_create(&consumers[i],NULL,&consume,NULL);
  }
  
  for(int i=0;i<NThreads;i++){
    pthread_join(producers[i],NULL);
    pthread_join(consumers[i],NULL);
  }
  
  printf("Printing array buff: \n");
	for (int i = 0; i < MAX_CAPACITY; i++)
	{
		printf("%d\n", buff[i]);
	}
	return 0;
}
