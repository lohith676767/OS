#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define SHM_NAME "/word_count_shm"
#define SIZE 1024

int main(){

      int shm_fd;
      char *ptr;

      shm_fd = shm_open(SHM_NAME,O_CREAT | O_RDWR,0666);
      ftruncate(shm_fd,SIZE);

      ptr =(char *)mmap(0,SIZE,PROT_READ | PROT_WRITE,MAP_SHARED,shm_fd,0);
      printf("Parent Process:\n");
      printf("Enter a sentence to count the number of words: ");
      fgets(ptr, SIZE, stdin);

      pid_t pid = fork();
      if(pid>0){
             wait(NULL);
             munmap(ptr,SIZE);
             shm_unlink(SHM_NAME);
      }else if(pid==0){
             int count = 0;
             char *str = ptr;
             int in_word=0;

             while(*str != '\0'){
                    if(*str == ' ' || *str == '\t'){
                           in_word=0;
                    }else if (in_word == 0){
                           in_word = 1;
                           count ++;
                    }
                    str++;
             }
             printf("Child process:\n");
             printf("Number of words: %d\n", count);
             munmap(ptr, SIZE);
      }
}
