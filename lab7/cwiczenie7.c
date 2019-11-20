#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char* argv[])
{
	char c;
	float size = 50;
	int fd_in;
	int fd_out;
	int sz;
	int tryb_x=0;
	int tryb_z=0;
	int tryb_n=0;
	int tryb=0;
	char *buff = (char*)calloc(100, sizeof(char));

	while( (c = getopt(argc, argv, "zxN:")) != -1)
	{
		switch(c)
		{
			case 'z':
				tryb=2;
				tryb_z=1;
				//printf("z\n");
				break;
			case 'x':				
				tryb=1;
				tryb_x=1;
				//printf("x\n");
				break;
			case 'N':
				tryb_n=1;		
				size = strtof(optarg, NULL);
				//printf("%f\n", size);
				break;
			default:
				printf("invalid flags, bye.");
		}
	}


if (tryb_x && tryb_z)
{
	printf("sprzeczne tryby pracy");
	return -1;
}

if (!tryb) 
{
	printf("Podaj parametr x lub z!!");
	return -2;
}
if (tryb_z && tryb_n)
{
	printf("Use n only with flag x!");
	return -3;
}
if (!(argc-optind==1 || argc-optind==2))
{
	printf("Error number of parameters!!");
	return -4;
}
printf("%s\n",argv[optind]);

printf("%f",size);
printf("\n\nOK\n\n");
return 0;
}
