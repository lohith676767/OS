#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
char buffer[1024];
int bytes_read;

int main(int argc,char*argv[]){
    if(argc!=3){
        perror("only 3 arg allowed");
        exit(1);
    }
    int source = open(argv[1],O_RDONLY);
    if(source<0){
        perror("cant open source");
        exit(1);
    }
    int destination = creat(argv[2],0777);
    if(destination<0){
        perror("cant open destination");
        exit(1);
    }

    if(access(argv[2],F_OK)==0){
        printf("overwrite %s: (Y/N): ",argv[2]);
        char answer = getchar();
        if(answer!='y'&&answer!='Y'){
            printf("cancelled\n");
            close(source);
            exit(0);
        }
    }

    while((bytes_read=read(source,buffer,sizeof(buffer)))){
        write(destination,buffer,bytes_read);
    }
    close(source);
    close(destination);
    return 0;
}
