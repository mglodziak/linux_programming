#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

int main()
{

	struct timespec time, time2;
	time.tv_sec=2;
	time.tv_nsec=100;
	for (int i=0;i<9;i++)
	{
	printf("Prosze mnie odblokowac!(%d)\n", getpid());
	raise(SIGSTOP);

	printf("Dziekuje uprzejmie.\n");
	nanosleep(&time, &time2);
	}
//	raise(SIGCONT);
}
