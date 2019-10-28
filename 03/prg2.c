#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


void end(int arg1, void* arg2)
{
printf("file exit, some data is writing.. \n");

unsigned int* x = (unsigned int*)arg2;

if (close(*x)) printf("zjebałeś zamykanie\n");
free(arg2);

}


int main(int argc, char* argv[])
{
	for (int i=1; i<argc; i++)
	{
		unsigned int* fd = (unsigned*)malloc(sizeof(int)); 
		*fd=open(argv[i],O_CREAT|O_WRONLY|O_EXCL,0666);

		if (*fd!=-1)
		{
			on_exit(end,(void*)fd);

		}
		else 
		{
			printf("File %s exist. Aborting...\n", argv[i]);
		}

	}


	return 0;
}
