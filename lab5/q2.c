#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void swapstrings(char **a, char **b){
  char *temp = *a;
  *a = *b;
  *b = temp;
}

void bubblesort(char *argv[],int argc){
  for(int i=0;i<argc;i++){
    for(int j=0;j<argc-i-1;j++){
      if(strcmp(argv[j],argv[j+1])>0){
        swapstrings(&argv[j],&argv[j+1]);
      } 
    }
  }
}

int main(int argc, char *argv[]){
  pid_t pid = fork();
  if(pid == -1){
    perror("Forking failed!!");
  }
  
  else if(pid == 0){
    printf("Child Process!\n");
    bubblesort(argv,argc);
    printf("Sorted Strings");
    for(int i=0;i<argc;i++){
      printf("%s\n",argv[i]);
    }
  }
  
  else{
    int status;
    wait(&status);
    printf("Parent Process!\n");
    printf("Unsorted Strings");
    for(int i=0;i<argc;i++){
      printf("%s\n",argv[i]);
    }
  } 
}
