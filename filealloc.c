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

}Fileinfo;

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

     



