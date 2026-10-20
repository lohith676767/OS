#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

typedef struct Block{

  int block_id;
  char filename[50];
  int is_free;
  struct Block* next_mem_block;
  struct Block* next_file_block;//linked
  int file_block_table[100];//indexed
  int table_size;

}Block;

typedef struct{

  char name[50];
  int size;
  int blocks_needed;
  int start_block;
  int end_block;
  int index_block;
  int allocated;

}FileInfo;

Block* memory_head = NULL;
int total_blocks =0;

void initialise(int n){
   total_blocks = n;
   Block* temp = NULL;
   for(int i=1;i<=n;i++){
     Block * newBlock = (Block*)malloc(sizeof(Block));
     newBlock->block_id = i;
     strcpy(newBlock->filename,"");
     newBlock->is_free = 1;
     newBlock->next_mem_block = NULL;
     newBlock->next_file_block = NULL;
     newBlock->table_size=0;

     if(memory_head==NULL){
       memory_head = newBlock;
       temp = memory_head;
     }else{
       temp->next_mem_block = newBlock;
       temp = newBlock;
     }
   }
}

void resetMemory() {
    Block* temp = memory_head;
    while (temp != NULL) {
        temp->is_free = 1;
        strcpy(temp->filename, "");
        temp->next_file_block = NULL;
        temp->table_size = 0;
        temp = temp->next_mem_block;
    }
}

Block* getBlockById(int id) {
    Block* temp = memory_head;
    while (temp != NULL) {
        if (temp->block_id == id)
            return temp;
        temp = temp->next_mem_block;
    }
    return NULL;
}

int getFreeBlockCount(){

  int count =0;
  Block* temp = memory_head;
  while(temp!=NULL){
    if(temp->is_free==1)count++;
    temp= temp->next_mem_block;
  }
  return count;
 
}


void contigousAlloction(FileInfo files[],int num_files){

  resetMemory();
  printf("\nCONTIGUOUS ALLOCATION\n");
  printf("Directory\n");
  printf("%-15s %-10s %-10s\n", "File Name", "Start", "Length");
  for(int i=0;i<num_files;i++){
    files[i].allocated = 0;
    int attempts = 0;
    int max_attempts = 999;
    while(attempts<max_attempts){
      int start_id = (rand()%total_blocks)+1;
      int all_free=1;
      for(int j =0;j<files[i].blocks_needed;j++){
        Block *b = getBlockById(start_id+j);
        if(b==NULL||b->is_free=0){
           all_free=0;
           break;
        }
      }
      if(all_free){
        for(int j =0;j<files[i].blocks_needed;j++){
          Block* b = getBlockById(start_index+j);
          b->is_free=0;
          strcpy(b->filename,files[i].name);
          files[i].start_block = start_id;
          files[i].allocated=1;
          printf("%-15s %-10d %-10d\n", files[i].name, files[i].start_block, files[i].blocks_needed);
          break;
        }
      }
      attempts++;
    }
    if (!files[i].allocated) {
      printf("%-15s %-10s %-10s (Not enough contiguous memory)\n", files[i].name, "-", "-");
    }
  }
}


void linkedAllocation(FileInfo files[], int num_files) {
    resetMemory();
    printf("\nLINKED ALLOCATION\n");
    printf("Directory\n");
    printf("%-15s %-10s %-10s\n", "File Name", "Start", "End");
    for(int i=0;i<num_files;i++){
       if((files[i].blocks_needed)>getFreeBlockCount()){
           printf("%-15s %-10s %-10s (Not enough total memory)\n", files[i].name, "-", "-");
           files[i].allocated = 0;
           continue;
       }
       int first_block = -1;
       int prev_block = -1;
       files[i].allocated=1;
       for(int j=0;j<files[i].blocks_needed;j++){
           int b_id;
           Block *b;
           do{
               b_id = (rand()%total_blocks)+1;
               b=getBlockById(b_id);
           }while(b->is_free==0);
           b->is_free=0;
           strcpy(b->filename,files[i].name);
           b->next_file_block = NULL;
           if(first_block == -1){first_block=b_id;}
           if(prev_block!=-1){
               Block * pb = getBlockById(prev_block);
               pb->next_file_block = b;
           }
           prev_block = b_id;
       }
       files[i].start_block = first_block;
       files[i].end_block = prev_block;
       printf("%-15s %-10d %-10d",files[i].name,files[i].start_block,files[i].end_block);
    }
    printf("\nIndvidual Listing \n");
    for(int i =0;i<num_files;i++){
        if(files[i].allocated){
            printf("%-15s ", files[i].name);
            Block* curr = getBlockById(files[i].start_block);
            while(curr!=NULL){
               printf("%d ", curr->block_id);
               curr = curr->next_file_block;
            }
            printf("\n");
        }
     }
}

void 
  
     



