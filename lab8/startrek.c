#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
int hp=100;

void decHP(int sig, siginfo_t *siginfo, void* context)
{
	hp-=10;
	printf("Trafiony dziad! Hp: %d\n",hp);
	if (hp<=0)
	{
		printf("wysylam kapsule ratunkowa");
		exit(1);
	}
}


int main (int argc, char* argv[])
{
struct sigaction act;
act.sa_sigaction=&decHP;

printf("Statek o id: %d\n", getpid());
sigaction(SIGTERM, &act, NULL);
while(1);
return 0;
}
