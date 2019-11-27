#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main()
{
	size_t f1;
	siginfo_t info;

	f1 = fork();
	if (f1==-1)
	{
		perror("FORK zdechl");
		return -1;
	}

	if( f1 == 0 )
	{
		execlp("./dziecko", "dziecko", NULL);
		printf ("nie udalo sie odpalic dzieciaczka\n");
	}
	else
	{	
		sleep(1);
		while(1){
			if (waitid( P_PID, f1, &info, WSTOPPED )==-1)
			{
				perror("waitid:");
				return -1;
			}
		
			if( info.si_code == CLD_STOPPED )
			{
				kill(f1, SIGCONT);
				//printf("Obudzono dziecko\n");
			}
			
			else
			{
				perror("Nie ma juz wiecej potomkow..\n");
				return 0;
			}
		}
	}
}
