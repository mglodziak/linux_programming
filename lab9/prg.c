#include <time.h>
#include <stdio.h>
#include <errno.h>

int main (int argc, char* argv[])
{

	struct timespec time;
//	if (!clock_gettime(CLOCK_REALTIME, &time))
//		printf("Clock realtime..%i", time  );
//
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
		printf("CLOCK_REALTIME_COARSE res: %ld.%09lds\n",time.tv_sec, time.tv_nsec);
	}
	else if (errno==EINVAL)
	{
		printf("Clock not supported");
	}


printf("\n\n");
struct timespec t1;
struct timespec t2;
struct timespec ref={0,1};
clock_gettime(CLOCK_REALTIME, &t1);
nanosleep(&ref,NULL);
clock_gettime(CLOCK_REALTIME, &t2);
printf("%li\n",t2.tv_nsec-t1.tv_nsec);


return 0;
}
