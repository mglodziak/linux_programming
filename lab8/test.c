#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
int main(int argc, char* argv[])
{

int fd;


//name="snowman10";
fd=open("snowman10.txt",O_RDONLY);
if (fd==-1)
{
	printf("chujowo");
	return -1;
}
char* buf = (char*)calloc(2048,sizeof(char));
if (read(fd,buf,2048)==0)
{
	printf( "strasznie chujowo ");
	return -2;
}

printf("%s",buf);
close(fd);

return 0;
}
