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

#define ZAKRES 5

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
    unlink(FI);
    unlink(FO);
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
    
    
    FO_fd=open(FI, O_RDWR | O_NONBLOCK);
    if (FO_fd==-1)
    {
        perror("Opening FO\n");
        return -2;
    }
    printf("Fo opened\n");
    
    struct timespec time_struct;
    time_struct.tv_sec=1;
    time_struct.tv_nsec=0;
    
    int random;
    char *c=(char*)malloc(sizeof(char));
        
    while(1)
    {
        if (read(FO_fd,c,1)<=0)
        {
        srand(time(0));
        random=rand()%ZAKRES+2;
        printf("%d\n", random);
        for (int i =0; i<random ; i++)
        {
            if (write(FO_fd, "1", 1)==-1)
            {
                perror("Writing FO err");
                return -3;
                
            }
            
        }
        nanosleep(&time_struct, NULL);
        }
        else 
        {
            if (write(FO_fd, "1", 1)==-1)
            {
                perror("Writing FO err");
                return -3;
                
            }
            nanosleep(&time_struct, NULL);
            continue;
        }
        
    }
    
       // atexit(close_fd);
    
    free(c);
    return 0;
}
