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

int main(int argc, char* argv[])
{
    FI_fd=open(FI, O_WRONLY);
    if (FI_fd==-1)
    {
        perror("Opening FI\n");
        return -2;
    }
    printf("Fi opened\n");
    
    
    FO_fd=open(FI, O_RDONLY);
    if (FO_fd==-1)
    {
        perror("Opening FO\n");
        return -2;
    }
    printf("Fo opened\n");
    
    //robię dupa, żeby procesy mogły walczyć o dostęp do pliku
    FO_fd=dup2(FO_fd, 69);
    if (FO_fd == -1)
    {
     perror("Dup sie...zDUPcył, no czyli nie dziala...");
     exit(EXIT_FAILURE);
    }
    
    struct timespec time_struct;
    time_struct.tv_sec=1;
    time_struct.tv_nsec=0;
    
    char *c=(char*)malloc(sizeof(char));
    pid_t child_pid;
    while(1)
    {
        int read_returns=read(FO_fd, c, 1);
        if (read_returns==-1)
        {
         perror("reading FO");
         exit(EXIT_FAILURE);
        }
        /*
        if (read_returns>0)
        {
            child_pid=fork();
            if (child_pid==-1)
            {
                perror("Creation child went wrong");
                exit(EXIT_FAILURE);
            }
            printf("Child created w chuj\n");
            
        }
        */
        printf("%s\n",c);
        nanosleep(&time_struct, NULL);
        
    }
    free(c);
}
