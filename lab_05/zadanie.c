#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
	siginfo_t infop;
	for (int i=1; i< argc; i++)
	{
		if (!fork())
		{
			printf("Potomek nr %d, parametr %s\n",i, argv[i]);
			execlp("sleep","sleep", argv[i],NULL);
		}

	}
	
	struct timespec time;
	time.tv_sec=0;
	time.tv_nsec=9999;

	do
	{
	int w = waitid(P_ALL,1,&infop, WEXITED | WNOHANG);
	if (w == -1)
	{
		return 0;
	}

		if (!w && infop.si_pid)
		{
			printf("PID: %d, status: %d\n",infop.si_pid, infop.si_status);

		}
		
		nanosleep(&time,NULL);
	}while(1);
	
	
return 0;
}
