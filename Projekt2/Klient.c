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
#define TIMER_SIG SIGUSR1
#define CLOCK_ID CLOCK_REALTIME

static void handler(int signal);
int flag = 0;

int FI_fd =-1;
int FO_fd =-1;

int main(int argc, char* argv[])
{
    while (FI_fd==-1)
    {
        FI_fd=open(FI, O_WRONLY);
        
        /*if (FI_fd==-1)
         *   {
         *       perror("Opening FI\n");
         *       return -2;
    }
    */
    }
    printf("Fi opened\n");
    printf("fofd = %d\n",FO_fd);
    while (FO_fd==-1)
    {
        FO_fd=open(FO, O_RDONLY);
        printf("fofd = %d\n",FO_fd);
        /*if (FO_fd==-1)
         *   {
         *       perror("Opening FO\n");
         *       return -2;
    }
    */
    }
    printf("fofd = %d\n",FO_fd);
    printf("Fo opened\n");
    
    //robię dupa, żeby procesy mogły walczyć o dostęp do pliku
    
    FO_fd=dup2(FO_fd, 69);
    if (FO_fd == -1)
    {
        perror("Dup sie...zDUPcył, no czyli nie dziala...");
        exit(EXIT_FAILURE);
    }
    
    
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
    
    
    
    char *c=(char*)malloc(sizeof(char));
    pid_t child_pid;
    
    
    
    if (timer_settime(timerid, 0, &trigger, NULL))
    {
        perror("timer");
        return -12;
    }
    pause();
    
    int count_of_children=0;
    pid_t ppid;
    char str[10];
    while(1)
    {
        
        if (flag)
        {
            
            int read_returns=read(FO_fd, c, 1);
            // printf("rr: %d\n",read_returns);
            if (read_returns==0)
                continue;
            
            if (read_returns==-1)
            {
                if (errno==EINTR)
                    continue;
                
                else
                {
                    perror("reading FO");
                    exit(EXIT_FAILURE);
                }
            }
            
            if (read_returns>0)
            {
                child_pid=fork();
                count_of_children++;
                if (child_pid==-1)
                {
                    perror("Creation child went wrong");
                    exit(EXIT_FAILURE);
                }
                else if (child_pid==0)
                {
                    
                    printf("I am child process my ID is   =  %d\n" , getpid());
                    
                }
                ppid=getpid();
                
                sprintf(str, "%d",ppid);
                
                if(count_of_children==1)
                {
                    setenv("PID_GROUP",str,0);
                    setpgid(ppid, ppid);
                }
                else
                {
                    char * pid_return=getenv("PID_GROUP");
                    int pid_ret=strtol(pid_return,NULL, 10);
                    setpgid(ppid, pid_ret);
                    
                }
                pid_t dupa = getpgid(ppid);
                printf ("GPID: %d\n",dupa);
                
            }            
            char* dupa= getenv("PID_GROUP");
            printf("No children: %d\n", count_of_children);
            printf("PD: %s\n", dupa);
            
            
            
            if (count_of_children >=3)
            {
                printf("\n\nMam 3 potomków\n");
                pid_t rodzic;
                pid_t grupa;
                rodzic=getpid();
                grupa=getpgid(rodzic);
                printf("rodzic: %d, grupa: %d\n",rodzic, grupa);
              
                char str_r[5];
                char str_g[5];
                char * buf = (char*)malloc(2+strlen(str_g)+strlen(str_r));
                sprintf(str_r, "%d",rodzic);
                sprintf(str_g, "%d",grupa);
                strcpy(buf, str_r);
                strcat(buf, "X");
                strcat(buf, str_g);
                
                printf("buf: %s\n\n", buf);
                if (write(FI_fd, buf, strlen(buf))==-1)
                     {
                        perror("Writing FI err");
                        return -5;
                        
                    }
                free(buf);
            }
            
        }
        flag=0;
    }
    free(c);
}

static void handler(int signal)
{
    flag = 1;
}
