#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>

int main(){
  pid_t pid;
  pid = fork();
  if(pid == 0){
    printf("Child Process");
    printf("%d\n",getpid());
  }
  else if(pid > 0){
    int status;
    wait(&status);
    printf("Parent Process");
    printf("%d\n",,getppid());
  }
  return 0;
}
