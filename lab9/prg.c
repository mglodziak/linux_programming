#include <time.h>
#include <stdio.h>
#include <errno.h>

int main (int argc, char* argv[])
{

	struct timespec time;
//	if (!clock_gettime(CLOCK_REALTIME, &time))
//		printf("Clock realtime..%i", time  );
//
// rozdzielczość
//
printf("Rozdzielczosc zegarow\n\n");
	if (!clock_getres(CLOCK_REALTIME, &time))
	{
		printf("CLOCK_REALTIME res: %ld.%09lds\n",time.tv_sec, time.tv_nsec);
	}
	else if (errno==EINVAL)
	{
		printf("Clock not supported");
	}

	if (!clock_getres(CLOCK_MONOTONIC, &time))
	{
		printf("CLOCK_MONOTONIC res: %ld.%09lds\n",time.tv_sec, time.tv_nsec);
	}
	else if (errno==EINVAL)
	{
		printf("Clock not supported");
	}

	if (!clock_getres(CLOCK_TAI, &time))
	{
		printf("CLOCK_TAI res: %ld.%09lds\n",time.tv_sec, time.tv_nsec);
	}
	else if (errno==EINVAL)
	{
		printf("Clock not supported");
	}

	if (!clock_getres(CLOCK_PROCESS_CPUTIME_ID, &time))
	{
		printf("CLOCK_PROCESS_CPUTIME_ID res: %ld.%09lds\n",time.tv_sec, time.tv_nsec);
	}
	else if (errno==EINVAL)
	{
		printf("Clock not supported");
	}


		if (!clock_getres(CLOCK_BOOTTIME, &time))
	{
		printf("CLOCK_BOOTTIME res: %ld.%09lds\n",time.tv_sec, time.tv_nsec);
	}
	else if (errno==EINVAL)
	{
		printf("Clock not supported");
	}
	
	if (!clock_getres(CLOCK_THREAD_CPUTIME_ID, &time))
	{
		printf("CLOCK_THREAD_CPUTIME_ID res: %ld.%09lds\n",time.tv_sec, time.tv_nsec);
	}
	else if (errno==EINVAL)
	{
		printf("Clock not supported");
	}
	
	if (!clock_getres(CLOCK_MONOTONIC_COARSE, &time))
	{
		printf("CLOCK_MONOTONIC_COARSE res: %ld.%09lds\n",time.tv_sec, time.tv_nsec);
	}
	else if (errno==EINVAL)
	{
		printf("Clock not supported");
	}

	if (!clock_getres(CLOCK_MONOTONIC_RAW, &time))
	{
		printf("CLOCK_MONOTONIC_RAW res: %ld.%09lds\n",time.tv_sec, time.tv_nsec);
	}
	else if (errno==EINVAL)
	{
		printf("Clock not supported");
	}

	if (!clock_getres(CLOCK_REALTIME_COARSE, &time))
	{
		printf("CLOCK_REALTIME_COARSE res: %ld.%09ld s\n",time.tv_sec, time.tv_nsec);
	}
	else if (errno==EINVAL)
	{
		printf("Clock not supported");
	}


printf("\n\n");



//opóźnienie nanosleepa
struct timespec t1;
struct timespec t2;
/*
struct timespec ref={1,0};
clock_gettime(CLOCK_REALTIME, &t1);
nanosleep(&ref,NULL);
clock_gettime(CLOCK_REALTIME, &t2);
printf("%li\n",t2.tv_nsec-t1.tv_nsec);
*/

printf("\n########\n");
printf("opóźnienia zegarów - srednia ze 100 pomiarow");
printf("\n########\n\n");

int opoznienie=0;
int res=0;
for (int i=0; i<100; i++)
{
clock_gettime(CLOCK_REALTIME, &t1);
clock_gettime(CLOCK_REALTIME, &t2);
opoznienie+=t2.tv_nsec-t1.tv_nsec;
}
res=opoznienie/100;
printf("0.%09ds CLOCK_REALTIME\n",res);

opoznienie=0;
res=0;
for (int i=0; i<100; i++)
{
clock_gettime(CLOCK_MONOTONIC, &t1);
clock_gettime(CLOCK_MONOTONIC, &t2);
opoznienie+=t2.tv_nsec-t1.tv_nsec;
}
res=opoznienie/100;
printf("0.%09ds CLOCK_MONOTONIC\n",res);

opoznienie=0;
res=0;
for (int i=0; i<100; i++)
{
clock_gettime(CLOCK_TAI, &t1);
clock_gettime(CLOCK_TAI, &t2);
opoznienie+=t2.tv_nsec-t1.tv_nsec;
}
res=opoznienie/100;
printf("0.%09ds CLOCK_TAI\n",res);

 
opoznienie=0;
res=0;
for (int i=0; i<100; i++)
{
clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t1);
clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t2);
opoznienie+=t2.tv_nsec-t1.tv_nsec;
}
res=opoznienie/100;
printf("0.%09ds CLOCK_PROCESS_CPUTIME_ID\n",res);  


opoznienie=0;
res=0;
for (int i=0; i<100; i++)
{
clock_gettime(CLOCK_BOOTTIME, &t1);
clock_gettime(CLOCK_BOOTTIME, &t2);
opoznienie+=t2.tv_nsec-t1.tv_nsec;
}
res=opoznienie/100;
printf("0.%09ds CLOCK_BOOTTIME\n",res);

opoznienie=0;
res=0;
for (int i=0; i<100; i++)
{
clock_gettime(CLOCK_THREAD_CPUTIME_ID, &t1);
clock_gettime(CLOCK_THREAD_CPUTIME_ID, &t2);
opoznienie+=t2.tv_nsec-t1.tv_nsec;
}
res=opoznienie/100;
printf("0.%09ds CLOCK_THREAD_CPUTIME_ID\n",res);
opoznienie=0;
res=0;
for (int i=0; i<100; i++)
{
clock_gettime(CLOCK_MONOTONIC_COARSE, &t1);
clock_gettime(CLOCK_MONOTONIC_COARSE, &t2);
opoznienie+=t2.tv_nsec-t1.tv_nsec;
}
res=opoznienie/100;
printf("0.%09ds CLOCK_MONOTONIC_COARSE\n",res);
opoznienie=0;
res=0;
for (int i=0; i<100; i++)
{
clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
opoznienie+=t2.tv_nsec-t1.tv_nsec;
}
res=opoznienie/100;
printf("0.%09ds CLOCK_MONOTONIC_RAW\n",res);

opoznienie=0;
res=0;
for (int i=0; i<100; i++)
{
clock_gettime(CLOCK_REALTIME_COARSE, &t1);
clock_gettime(CLOCK_REALTIME_COARSE, &t2);
opoznienie+=t2.tv_nsec-t1.tv_nsec;
}
res=opoznienie/100;
printf("0.%09ds CLOCK_REALTIME_COARSE\n",res);
return 0;
}
