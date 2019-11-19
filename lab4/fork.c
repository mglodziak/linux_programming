#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <getopt.h>

void get_args(int* argc, char** argv[], float *r, float *l, float *p)
{
int opt;

while ((opt=getopt(*argc, *argv, "r:l:p:")) != -1)
	switch(opt)
	{
		case 'r':
		*r=strtof(optarg, NULL);
		break;

		case 'l':
		*l=strtof(optarg,NULL);
		break;
		
		case 'p':
		*p=strtof(optarg, NULL);
		break;
		
		default:
		printf("Bad arguments");
		exit(EXIT_FAILURE);
	}
}


int main(int argc, char* argv[])
{
float r=0;
float l=0;
float p=0;

get_args(&argc, &argv, &r, &l, &p);
printf("%f, %f, %f\n", r, l, p);


for (int i=0; i<3; i++)
{
int pid=fork();

	if(!pid) //jeśli zero to podmieniam
	{
	//exec();
	break;
	}
}

return 0;
}
