#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define FI "./FI"
#define FO "./FO"

int FI_fd;
int FO_fd;


/*
void close_fd()
{
    if (close(FI_fd)==-1)
    {
        perror("Closing FI\n");
        return ;
    }
    if (close(FO_fd)==-1)
    {
        perror("Closing FO\n");
        return ;
    }
    return ;
}
*/

int main(int argc, char* argv[])
{
    
    if (mkfifo(FI, S_IRUSR | S_IWUSR | S_IWGRP) == -1 && errno != EEXIST)
    {
        perror("mkfifo FI creation \n");
        return -1;
    }
    printf("Fi created\n");
    
    if (mkfifo(FO, S_IRUSR | S_IWUSR | S_IWGRP) == -1 && errno != EEXIST)
    {
        perror("mkfifo FO creation \n");
        return -1;
    }
    printf("Fo created\n");
    
    FI_fd=open(FI, O_RDONLY);
    if (FI_fd==-1)
    {
        perror("Opening FI\n");
        return -2;
    }
    printf("Fi opened\n");
    
    
    FO_fd=open(FI, O_WRONLY);
    if (FO_fd==-1)
    {
        perror("Opening FO\n");
        return -2;
    }
    printf("Fo opened\n");
    
    struct timespec time;
    time.tv_sec=1;
    time.tv_nsec=0;
    
    while(1)
    {
     if (write(FO_fd, "1", 1)==-1)
     {
      perror("Writing FO err");
      return -3;
      
     }
     nanosleep(&time, NULL);
     
    }
    
//    atexit(close_fd);
    
    return 0;
}
