#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>

typedef struct RR{
  int id;
  int arrival_time;
  int burst_time;
  int remaining_time;
  int waiting_time;
  int priority;
}RR;

void RoundRobin(RR process[],int n,int quantum){
  int total_time = 0;
  int remaining_processes = n;
  
  while(remaining_processes > 0){
    for(int i=0;i<n;i++){
      if(process[i].remaining_time > 0 && process[i].arrival_time <= total_time){
        if(process[i].remaining_time <= quantum){
          total_time = total_time + process[i].remaining_time;
          process[i].remaining_time = 0;
          process[i].waiting_time = total_time - process[i].arrival_time - process[i].burst_time;
          printf("Process %d \t completed at: %d\n",process[i].id,total_time);
          remaining_processes--;
        }
        else{
          total_time = total_time + quantum;
          process[i].remaining_time -=quantum;
          printf("Process %d \t executed at: %d\n",process[i].id,total_time);
        }
      }
    }
  }
  printf("\n");
  float avg_wait_time = 0;
  for(int i=0;i<n;i++){
    avg_wait_time += process[i].waiting_time;
  }
  avg_wait_time /= n;
  printf("Avg waiting time : %.2f\n",avg_wait_time);
}

void swapProcess(RR *a, RR *b){
  RR *temp = a;
  a = b;
  b = temp;
}

int compare_burst_time(const void *a, const void *b) {
    const RR *rr1 = (const RR *)a;
    const RR *rr2 = (const RR *)b;
    return rr1->burst_time - rr2->burst_time;
}

void sortProcesses(RR process[],int n){
  qsort(process, n, sizeof(RR), compare_burst_time);
}

void SJF(RR process[], int n) {
    int total_time = 0;
    int completed_process = 0;
    
    sortProcesses(process,n);
    
    int completed[n];
    for(int i=0;i<n;i++){
      completed[i] = 0;
    }
    
    while(completed_process < n){
      int shortest_burst_time = 9999999;
      int shortest_burst_index = -1;
      
      for(int i=0;i<n;i++){
        if(process[i].arrival_time <= total_time && completed[i]==0 && process[i].burst_time < shortest_burst_time){
          shortest_burst_time = process[i].burst_time;
          shortest_burst_index = i;
        }
      }
      
      if(shortest_burst_index != -1){
        total_time += process[shortest_burst_index].burst_time;
        process[shortest_burst_index].waiting_time = total_time - process[shortest_burst_index].arrival_time - process[shortest_burst_index].burst_time;
            completed[shortest_burst_index] = 1;
            completed_process++;
        
        printf("| P%d (%d)",process[shortest_burst_index].id,total_time);
      }
      else{
        total_time++;
      }
    }
    printf("\n");
    
    float avg_wait = 0;
    for(int i=0;i<n;i++){
      avg_wait += process[i].waiting_time;
    }
    avg_wait /= n;
    printf("Avg wait : %.2f",avg_wait);
}

void priority_scheduling(RR process[],int n){
  int total_time = 0;
  int completed_process = 0;
  
  int completed[n];
  for(int i=0;i<n;i++){
    completed[i] = 0;
  }
  
  while(completed_process < n){
    int highest_priority = -99999;
    int highest_priority_index = -1;
    
    for(int i=0;i<n;i++){
      if(process[i].arrival_time <= total_time && completed[i] == 0 && process[i].priority > highest_priority){
        highest_priority = process[i].priority;
        highest_priority_index = i;
      }
    }
    
    if(highest_priority != -1){
      total_time += process[highest_priority_index].burst_time;
      process[highest_priority_index].waiting_time = total_time - process[highest_priority_index].arrival_time - process[highest_priority_index].burst_time;
      completed[highest_priority_index] = 1;
      completed_process++;
      
      printf("| P%d (%d)",process[highest_priority_index].id,total_time);
    }
    else{
      total_time++;
    }
  }
  printf("\n");
  
  float avg_wait = 0;
    for(int i=0;i<n;i++){
      avg_wait += process[i].waiting_time;
    }
    avg_wait /= n;
    printf("Avg wait : %.2f",avg_wait);
}


int main(){
  int no_of_process;
  printf("Enter no of Process:");
  scanf("%d",&no_of_process);
  RR process[no_of_process];  
  for(int i=0;i<no_of_process;i++){
    printf("Enter ProcessID: ");
    scanf("%d",&process[i].id);
    printf("Enter Arrival Time: ");
    scanf("%d",&process[i].arrival_time);
    printf("Enter burst Time: ");
    scanf("%d",&process[i].burst_time);
    
    process[i].remaining_time = process[i].burst_time;
  }
  
  int ch;
  printf("Enter\n1.Round Robin Scheduling\n2.Shortest-Job First Scheduling\n3.Priority Scheduling");
  scanf("%d",&ch);
  switch(ch){
    case 1:
      int time_quantum;
      printf("Enter Time Quantum for Round Robin:");
      scanf("%d",&time_quantum);
      RoundRobin(process,no_of_process,time_quantum);
    case 2:
      SJF(process,no_of_process);
    case 3:
      for(int i=0;i<no_of_process;i++){
        printf("Enter Priority: ");
        scanf("%d",&process[i].priority);
      }
      priority_scheduling(process,no_of_process);
  }
  return 0;
}
