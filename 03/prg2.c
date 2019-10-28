#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


void dupa(int arg1, void* arg2)
{
printf("file exit, some data is writing.. \n");

//char* c = (char*)calloc(100,sizeof(char));
//c="dupa";
//int noBytes =10;
//write(arg1, c, noBytes);
//free(c);

//close(arg1);

if (close(arg2)) printf("zjebałeś zamykanie\n");

}


int main(int argc, char* argv[])
{
	for (int i=1; i<argc; i++)
	{
		int fd=open(argv[i],O_CREAT|O_WRONLY|O_EXCL,0666);
		if (fd!=-1)
		{
			on_exit(dupa,(void*)fd);

		}
		else 
		{
			printf("File %s exist. Aborting...\n", argv[i]);
		}

	}


	return 0;
}
