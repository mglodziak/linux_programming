#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>


int main(int argc, char* argv[])
{
	if(argc < 1)
		perror("Liczba argumentow");
	
	int p[2];
	int nChild = strtol(argv[1], NULL, 10);


	printf("ilosc: %i\n", nChild);

	if( pipe(p) < 0 )
		perror("Pipe");

	for(int i = 0; i<nChild; i++)
	{
		pid_t pid = fork();

		if( pid == -1 )
		{
			perror("dzieciaczek");
			return -10;
		}

		else if (pid == 0)
		{
			int buf;
			while(read(p[0], &buf, 1) > 0)
			{
				printf("Wrzuciles: %i\n", buf);
				if (buf==0)
					continue;
				else if (buf ==255)
				{
					printf("Otrules mnie, dziadu!\n");
					break; //trucizna 
				}
				--buf;
				write(p[1], &buf, 1);

			}
			close(p[1]);
			close(p[0]);
			exit(0);
		}
	}
	int buf2=255;
	write(p[1], &buf2, 1);


	return 0;
}
