#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typdef struct {

       int id;int at;int bt;int pr;int ct;int tat;int wt;int rt;int is_completed;

}Process;

typdef struct{

       int id;int start;int end;

}Gantt;

Gantt gantt[20];
int gantt_size = 0;

void add_to_gantt(int id,int st, int et){

      if(gantt_size>0 && gantt[gantt_size-1].id==id && gant[gantt_size-1].end = st){
             gantt[gantt_size-1].end = et;
      }else{
             gantt[gantt_size].id = id;
             gantt[gantt_size].start = st;
             gantt[gantt_size].end = et;
             gantt_size++;
      }
}

void printTable(Process p[], int n) {
    float total_tat = 0, total_wt = 0;
    printf("\nOutput:\n");
    printf("| Process ID | Arrival Time | Burst Time | Turnaround Time | Waiting Time |\n");
    for (int i = 0; i < n; i++) {
        printf("| P%-9d | %-12d | %-10d | %-15d | %-12d |\n",
               p[i].id, p[i].at, p[i].bt, p[i].tat, p[i].wt);
        total_tat += p[i].tat;
        total_wt += p[i].wt;
    }
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
    printf("Average Waiting Time: %.2f\n", total_wt / n);
}

void printGantt() {
    printf("\nGantt Chart:\n|");
    for (int i = 0; i < gantt_size; i++) {
        if (gantt[i].id == -1) printf(" IDLE |");
        else printf("  P%d  |", gantt[i].id);
    }
    printf("\n%d", gantt[0].start);
    for (int i = 0; i < gantt_size; i++) {
        if (gantt[i].id == -1) printf("      %d", gantt[i].end);
        else printf("       %d", gantt[i].end);
    }
    printf("\n");
}

void fcfc(Process p[],in n){
       for(int i = 0;i<n;i++) p[i].is_completed = 0;
       int current_time =0;
       int completed = 0;
       gantt_size = 0;

       while(completed<n){
              int idx=-1;
              int min_at = 99999;
              for(int i = 0;i<n;i++){
                     if(p[i].is_completed==0 && p[i].at <= current_time){
                            if(p[i].at < min_at){
                                   min_at = p[i].at;
                                   idx = i;
                            }else if(p[i].at == min_at){
                                   if(idx==-1||p[i].pid < p[idx].id) idx = i;
                            }
                     }
              }
              if(idx!=-1){
                     add_to_gantt(p[idx].id,current_time,current_time+p[idx].bt);
                     current_time+=p[idx].bt;
                     p[idx].is_completed = 1;
                     p[idx].ct = current_time;
                     p[idx].tat = p[idx].ct-p[idx].at;
                     p[idx].wt = p[idx].tat -p[idx].bt;
                     completed++;
              }else{
                     int next_at = 99999;
                     for(int i = 0;i<n;i++){
                            if(p[i].is_completed == 0 && p[i].at < next_at){
                                   next_at = p[i].at;
                            }
                     }
                     add_to_gantt(-1,current_time,next_at);
                     current_time = next_at;
              }
       }
       printTable(p,n);
       printGantt():
}

