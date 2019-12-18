#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
 
#define TIMER_SIG SIGRTMIN+4
#define TIMER_SIGSL SIGRTMIN+3
#define CLOCK_ID CLOCK_REALTIME
 
int i = 1;
sigset_t set;
int blockingState = 0;
 
void timespecFromStr(char* str, struct timespec *ts);
float getMultipier(char* p);
void getArguments(struct timespec* ts, int* argc, char** argv[]);
static void handler(int sig, siginfo_t* si, void* uc);
static void handlerBlocker(int sig, siginfo_t* si, void* uc);
 
 
int main(int argc, char* argv[])
{
    timer_t timerId[2];
    struct itimerspec itsp[2];
    struct timespec ts;
    struct sigaction sa;
    struct sigevent sev[2]; //tablica struktur
    struct sigaction act;
 
    getArguments(&ts, &argc, &argv);
    int counter;
 
    sigemptyset(&set);
    sigaddset(&set, TIMER_SIG); //sigrtmin+4
 
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handler;
    sigemptyset(&sa.sa_mask);
    if (sigaction(TIMER_SIG, &sa, NULL) == -1)
    {
        perror("sigaction");
        _exit(EXIT_FAILURE);
    }
 
    act.sa_flags = SA_SIGINFO;
    act.sa_sigaction = handlerBlocker;
    sigemptyset(&act.sa_mask);
    if (sigaction(TIMER_SIGSL, &act, NULL) == -1)
    {
        perror("sigaction");
        _exit(EXIT_FAILURE);
    }
 
    sev[0].sigev_notify = SIGEV_SIGNAL;
    sev[0].sigev_signo = TIMER_SIG; 
    sev[0].sigev_value.sival_ptr = &timerId[0];
    if(timer_create(CLOCK_ID, &sev[0], &timerId[0]) < 0)
    {
        perror("timer_create\n");
        _exit(EXIT_FAILURE);
    }
 
    sev[1].sigev_notify = SIGEV_SIGNAL;
    sev[1].sigev_signo = TIMER_SIGSL;
    sev[1].sigev_value.sival_ptr = &timerId[1];
    if(timer_create(CLOCK_ID, &sev[1], &timerId[1]) < 0)
    {
        perror("timer_create\n");
        _exit(EXIT_FAILURE);
    }
 
    itsp[0].it_interval = ts;
    itsp[0].it_value = ts;
    if(timer_settime(timerId[0], 0, &itsp[0], NULL))
    {
        perror("timer_settime");
        _exit(EXIT_FAILURE);
    }
 
    long tmp = ts.tv_sec  * 3500000000 + ts.tv_nsec;
	//tu działa ten drugi budzik
    itsp[1].it_interval.tv_sec = tmp / 1000000000;
    itsp[1].it_interval.tv_nsec = tmp - (itsp[1].it_interval.tv_sec * 1000000000);
    itsp[1].it_value = itsp[1].it_interval;
 
    if(timer_settime(timerId[1], 0, &itsp[1], NULL))
    {
        perror("timer_settime");
        _exit(EXIT_FAILURE);
    }
 
 
    counter = 0;
    printf("\x1b[H\x1b[J\n");
    printf("\x1b[2;1H<\x1b[2;20H>\n");
    printf("\x1b[5;1H%d\n", counter);
    while(1)
    {      
        pause();
        if(i < 20)
            printf("\x1b[2;%dH#\n", i);
        else
        {
            i = 1;
            counter++;
            printf("\x1b[2;1H\x1b[K\n");
            printf("\x1b[2;1H<\x1b[2;20H>\n");
        }
        printf("\x1b[5;1H%d\n", counter);
    }
 
    _exit(EXIT_SUCCESS);
}
 
//=============================================
 
float getMultipier(char* p)
{
 
        if(!strcmp(p, "s"))
            return 1;
        else if (!strcmp(p, "ds"))
            return 10;
        else if (!strcmp(p, "des"))
            return 1.0 / 10;
        else
            return 1;
}
 
void timespecFromStr(char* str, struct timespec *ts)
{
    char* p;
    float num = strtof(str, &p);
    num *= getMultipier(p);
    ts->tv_sec = 1000000000 * num / 1000000000;
    ts->tv_nsec = 1000000000 * (num - ts->tv_sec);
}
 
void getArguments(struct timespec* ts, int* argc, char** argv[])
{
    int opt;
    while((opt = getopt(*argc, *argv, "t:")) != -1)
    {
        switch(opt)
        {
            case 't':
            {
                timespecFromStr(optarg, ts);
                break;
            }
            default:
                printf("WRONG ARGUMENTS!");
                exit(-1);
        }
    }
}
 
static void handler(int sig, siginfo_t* si, void* uc)
{
    i++;
}
 
static void handlerBlocker(int sig, siginfo_t* si, void* uc)
{
    if(blockingState)
    {
        sigprocmask(SIG_UNBLOCK, &set, NULL);
        blockingState = 0;
    }
    else
    {
        sigprocmask(SIG_BLOCK, &set, NULL);
        blockingState = 1;
    }
}
