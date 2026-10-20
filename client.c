#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define SHM_NAME "/chat_shm"
#define SIZE 1024

struct chat_data{
    int status;
    char message[1024];
};

int main(){

       int shm_fd = shm_open(SHM_NAME,O_RDWR,0666);
       struct chat_data *ptr = mmap(0,SIZE,PROT_READ|PROT_WRITE,MAP_SHARED,shm_fd,0);
      
       while(1){
            while(ptr->status !=0 && ptr->status != -1){
                   if(ptr->status == -1) break;
                   if (strlen(ptr->message) > 0) {
                          printf("Received from server: %s\n", ptr->message);}
                   printf("Client: ");
                   fgets(ptr->message, 1024, stdin);
                   ptr->message[strcspn(ptr->message, "\n")] = 0;
        
                   if (strcmp(ptr->message, "Bye") == 0) {
                          ptr->turn = -1;
                          break;
                   }
                   ptr->turn = 1;
            }
       }
       munmap(ptr,SIZE);
}
