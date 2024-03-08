#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void swapstrings(char **a, char **b){
  char *temp = *a;
  *a = *b;
  *b = temp;
}

void bubblesort(char *str[],int n){
  for(int i=0;i<n;i++){
    for(int j=0;j<n-i-1;j++){
      if(strcmp(str[j],str[j+1])>0){
        swapstrings(&str[j],&str[j+1]);
      }
    }
  }
}

void selectionsort(char *str[],int n){
  for(int i=0;i<n-1;i++){
    int min = i;
    for(int j=i+1;j<n;j++){
      if(strcmp(str[j],str[min])>0){
        min = j;
      }
      if(min != i){
        swapstrings(&str[i],&str[min]);
      }
    }
  }
}

int main(){
  int n;
  printf("Enter no of strings:");
  scanf("%d",&n);
  char *str[n];
  for(int i=0;i<n;i++){
    str[i] = (char *)malloc(sizeof(char));
    scanf("%s",str[i]);
  }
  
  pid_t pid1 = fork();
  if(pid1 == -1){
    perror("Forking Failed!!");
    return -1;
  }
  else if (pid1 == 0){
    printf("Child Process 1\n");
    printf("Sorted Strings\n");
    bubblesort(str,n);
    for(int i=0;i<n;i++){
      printf("%s\n",str[i]);
    }
  }
  else{
    pid_t pid2 = fork();
    if(pid2 < 0){
      perror("Forking Failed!!");
      return -1;
    }
    else if (pid2 == 0){
    printf("Child Process 2\n");
    printf("Sorted Strings\n");
    selectionsort(str,n);
    for(int i=0;i<n;i++){
      printf("%s\n",str[i]);
    }
  }
    else{
      int status;
      wait(&status);
      printf("Parent Process\n");
      printf("Unsorted Strings\n");
      for(int i=0;i<n;i++){
        printf("%s\n",str[i]);
      }   
    }
  }
}
