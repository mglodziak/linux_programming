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
#define TIMER_SIG SIGHUP
#define CLOCK_ID CLOCK_REALTIME
#define ZAKRES 5

static void handler(int signal);
int flag = 0;

int FI_fd;
int FO_fd;

/*
 * 
 * void close_fd()
 * {
 *    if (close(FI_fd)==-1)
 *    {
 *        perror("Closing FI\n");
 *        return ;
 *    }
 *    if (close(FO_fd)==-1)
 *    {
 *        perror("Closing FO\n");
 *        return ;
 *    }
 *    return ;
 *   unlink(FI);
 *   unlink(FO);
 * }
 * 
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
    
    
    FO_fd=open(FO, O_RDWR | O_NONBLOCK);
    if (FO_fd==-1)
    {
        perror("Opening FO\n");
        return -2;
    }
    printf("Fo opened\n");
    
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = handler;
    if (sigaction(TIMER_SIG, &sa, NULL) == -1)
    {
        perror("signal");
        _exit(EXIT_FAILURE);
    }
    
    timer_t timerid;
    struct sigevent sev;
    struct itimerspec trigger;
    
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = TIMER_SIG;
    trigger.it_value.tv_sec = 1;
    trigger.it_value.tv_nsec = 0;
    trigger.it_interval.tv_sec = 1;
    trigger.it_interval.tv_nsec = 0;
    if (timer_create(CLOCK_ID, &sev, &timerid) < 0)
    {
        perror("timer_create");
        return -11;
    }
    
    int random;
    char *c=(char*)malloc(sizeof(char));
    
    while(1)
    {
        if (timer_settime(timerid, 0, &trigger, NULL))
        {
            perror("timer");
            return -12;
        }
        pause();
        if (flag)
        {
            
            printf("%ld\n",read(FO_fd,c,1));
            if (read(FO_fd,c,1)<=0)
            {
              
                srand(time(0));
                random=rand()%ZAKRES+1;
                printf("%d\n", random);
                for (int i =0; i<random ; i++)
                {
                    if (write(FO_fd, "1", 1)==-1)
                    {
                        perror("Writing FO err");
                        return -3;
                        
                    }
                    
                }
            }
            else 
            {
                continue;
            }
        }
        flag=0;
    }
    
    // atexit(close_fd);
    
    free(c);
    return 0;
}


static void handler(int signal)
{
    flag = 1;
}
