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

       int shm_fd = shm_open(SHM_NAME,O_RDWR | O_CREAT,0666);
       ftruncate(shm_fd,SIZE);
       struct chat_data *ptr = mmap(0,SIZE,PROT_READ|PROT_WRITE,MAP_SHARED,shm_fd,0);
       memset(ptr,0,SIZE);
       ptr->status = 0;
       printf("server started. waiting....\n");
       while(1){
            while(ptr->status !=1 && ptr->status != -1){
                   if(ptr->turn == -1) break;
                   printf("client : %s\n",ptr->message);
                   printf("Server : ");
                   fgets(ptr->message,1024,stdin);
                   if(strcmp(ptr->message,"Bye")==0){ptr->status = -1;break;}
                   ptr->status = 0;
            }
       }
       munmap(ptr,SIZE);
       shm_unlink(SHM_NAME);
}
