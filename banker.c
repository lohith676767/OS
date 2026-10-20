#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int Available[10],Max[10][10],Allocated[10][10],Need[10][10];
int n_resources,n_process;

void calculateNeed(){
    for(int i =0;i<n_process;i++){
        for(int j=0;j<n_resources;j++){
            Need[i][j] = Max[i][j]-Allocated[i][j];
        }
    }
}

void readData(){

    printf("Number of processes: ");
    scanf("%d", &n_processes);
    printf("Number of resources: ");
    scanf("%d", &n_resources);
    for (int j = 0; j < n_resources; j++) {
        printf("Number of Available instances of resource %c: ", 'A' + j);
        scanf("%d", &Available[j]);
    }

    for (int i = 0; i < n_processes; i++) {
        printf("Maximum requirement for P%d: ", i);
        for (int j = 0; j < n_resources; j++) {
            scanf("%d", &Max[i][j]);
        }
    }

    for (int i = 0; i < n_processes; i++) {
        printf("Allocated instances to P%d: ", i);
        for (int j = 0; j < n_resources; j++) {
            scanf("%d", &Allocation[i][j]);
        }
    }
    calculateNeed();
  
}

void printData() {
    printf("\nPid\tAlloc\tMax\tNeed\tAvailable\n");
    for (int i = 0; i < n_processes; i++) {
        printf("P%d\t", i);
        for (int j = 0; j < n_resources; j++) printf("%d ", Allocation[i][j]);
        printf("\t");
        
        for (int j = 0; j < n_resources; j++) printf("%d ", Max[i][j]);
        printf("\t");
        
        for (int j = 0; j < n_resources; j++) printf("%d ", Need[i][j]);
        printf("\t");
        
        if (i == 0) {
            for (int j = 0; j < n_resources; j++) printf("%d ", Available[j]);
        }
        printf("\n");
    }
}
bool is_safe(int safeSeq[]){

        int work[10];
        for(int i =0;i<n_resources;i++) work[i]=Available[i];
        boolean Finished[10]={false};
        int count =0;
        while(count<n_process){
               boolean found = false;
               for(int i =0;i<n_process;i++){
                      if(!Finished[i]){
                             int j;
                             for(j=0;j<n_resources;j++){
                                    if(Need[i][j]>work[j]){
                                           break;
                                    }
                             }
                             if(j==n_resources){
                                    for(int k=0;k<n_resources;k++){
                                           work[k]+=Allocated[i][k];
                                    }
                                    safeSeq[count++]=i;
                                    found = true;
                                    Finished[i]=true;
                             }
                      }
               }
               if(!found)return false;
        }
        return true;
}       

void resourceRequest(){

       char prefix;
       int pid;
       int request[10];
       printf("ENter process requesting resource : ");
       scanf(" %c%d",&prefix,&pid);
       printf("ENter the request vector : ");
       for(int j=0;j<n_resources;j++){scanf("%d",&request[j]);}
       for(int j=0;j<n_resources;j++){
              if(request[j]>Need[pid][j]{printf("cant exceed Max\n");return;}
       }
       for(int j=0;j<n_resources;j++){
              if(request[j]>Available[j]{printf("Wait\n");return;}
       } 
       for(int j =0;j<n_resources_j++){
              Available[j]-=request[j];
              Allocation[pid][j] += request[j];
              Need[pid[j]-= request[j];
       }
       int safeSeq[10];
       if(is_safe(safeSeq)){printf("request granted\n");}
       else{printf("Request not granted\n");
              for(int j=0;j<n_resqources;j++){
                     Allocation[pid][j] -= request[j];
                     Need[pid][j] += request[j];
                     Available[j] += request[j];
              }
       }
}

void printSafetySequence() {
    int safeSeq[10];
    if (isSafe(safeSeq)) {
        printf("Display the Safety Sequence: ");
        for (int i = 0; i < n_processes; i++) {
            printf("P%d ", safeSeq[i]);
        }
        printf("\n");
    } else {
        printf("System is currently in an unsafe state (Deadlock may occur).\n");
    }
} 

int main() {
    int option;
    while (1) {
        printf("\nBanker's Algorithm\n1. Read Data\n2. Print Data\n3. Resource request\n4. Print safety sequence\n5. Exit\nEnter the option: ");
        scanf("%d", &option);
        
        switch (option) {
            case 1: readData(); break;
            case 2: printData(); break;
            case 3: resourceRequest(); break;
            case 4: printSafetySequence(); break;
            case 5: return 0;
            default: printf("Invalid option\n");
        }
    }
    return 0;
}

