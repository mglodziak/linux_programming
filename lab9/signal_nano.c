#include <time.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>

#define ILOSC_POMIAROW 5
double j=1.0;

void obsluga_sigusr1(int numer) 
{
	puts("Dostalem sygnal SIGUSR1, powtarzam nanosleepa");
	struct timespec ref={j,0};
	nanosleep(&ref,NULL);
}




int main (int argc, char* argv[])
{

signal(SIGUSR1, obsluga_sigusr1);

struct timespec t1;
struct timespec t2;
int opoznienie=0;
int res=0;



printf("\n########\n");
printf("opóźnienia nanosleepa - srednia z %d pomiarow",ILOSC_POMIAROW);
printf("\n########\n\n");

for ( j=1.0;j<3.1;j+=0.5)
{
struct timespec ref={j,0};

printf("\n\nOpóźnienie nanosleepa %f sekundy\n\n",j);

for (int i=0; i<ILOSC_POMIAROW; i++)
{
clock_gettime(CLOCK_REALTIME, &t1);
nanosleep(&ref,NULL);
clock_gettime(CLOCK_REALTIME, &t2);
opoznienie+=t2.tv_nsec-t1.tv_nsec;
}
res=opoznienie/ILOSC_POMIAROW;
printf("0.%09ds CLOCK_REALTIME\n",res);

opoznienie=0;
res=0;
for (int i=0; i<ILOSC_POMIAROW; i++)
{
clock_gettime(CLOCK_MONOTONIC, &t1);
nanosleep(&ref,NULL);
clock_gettime(CLOCK_MONOTONIC, &t2);
opoznienie+=t2.tv_nsec-t1.tv_nsec;
}
res=opoznienie/ILOSC_POMIAROW;
printf("0.%09ds CLOCK_MONOTONIC\n",res);

opoznienie=0;
res=0;
for (int i=0; i<ILOSC_POMIAROW; i++)
{
clock_gettime(CLOCK_TAI, &t1);
nanosleep(&ref,NULL);
clock_gettime(CLOCK_TAI, &t2);
opoznienie+=t2.tv_nsec-t1.tv_nsec;
}
res=opoznienie/ILOSC_POMIAROW;
printf("0.%09ds CLOCK_TAI\n",res);

 
opoznienie=0;
res=0;
for (int i=0; i<ILOSC_POMIAROW; i++)
{
clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t1);
nanosleep(&ref,NULL);
clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t2);
opoznienie+=t2.tv_nsec-t1.tv_nsec;
}
res=opoznienie/ILOSC_POMIAROW;
printf("0.%09ds CLOCK_PROCESS_CPUTIME_ID\n",res);  


opoznienie=0;
res=0;
for (int i=0; i<ILOSC_POMIAROW; i++)
{
clock_gettime(CLOCK_BOOTTIME, &t1);
nanosleep(&ref,NULL);
clock_gettime(CLOCK_BOOTTIME, &t2);
opoznienie+=t2.tv_nsec-t1.tv_nsec;
}
res=opoznienie/ILOSC_POMIAROW;
printf("0.%09ds CLOCK_BOOTTIME\n",res);

opoznienie=0;
res=0;
for (int i=0; i<ILOSC_POMIAROW; i++)
{
clock_gettime(CLOCK_THREAD_CPUTIME_ID, &t1);
nanosleep(&ref,NULL);
clock_gettime(CLOCK_THREAD_CPUTIME_ID, &t2);
opoznienie+=t2.tv_nsec-t1.tv_nsec;
}
res=opoznienie/ILOSC_POMIAROW;
printf("0.%09ds CLOCK_THREAD_CPUTIME_ID\n",res);
opoznienie=0;
res=0;
for (int i=0; i<ILOSC_POMIAROW; i++)
{
clock_gettime(CLOCK_MONOTONIC_COARSE, &t1);
nanosleep(&ref,NULL);
clock_gettime(CLOCK_MONOTONIC_COARSE, &t2);
opoznienie+=t2.tv_nsec-t1.tv_nsec;
}
res=opoznienie/ILOSC_POMIAROW;
printf("0.%09ds CLOCK_MONOTONIC_COARSE\n",res);
opoznienie=0;
res=0;
for (int i=0; i<ILOSC_POMIAROW; i++)
{
clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
nanosleep(&ref,NULL);
clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
opoznienie+=t2.tv_nsec-t1.tv_nsec;
}
res=opoznienie/ILOSC_POMIAROW;
printf("0.%09ds CLOCK_MONOTONIC_RAW\n",res);

opoznienie=0;
res=0;
for (int i=0; i<ILOSC_POMIAROW; i++)
{
clock_gettime(CLOCK_REALTIME_COARSE, &t1);
nanosleep(&ref,NULL);
clock_gettime(CLOCK_REALTIME_COARSE, &t2);
opoznienie+=t2.tv_nsec-t1.tv_nsec;
}
res=opoznienie/ILOSC_POMIAROW;
printf("0.%09ds CLOCK_REALTIME_COARSE\n",res);
}
return 0;
}
