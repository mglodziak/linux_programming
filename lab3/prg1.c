#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int res=0; //zmienna globalna, mój zasób

void end()
{
	while(res>0)
	{
	printf("%i\n", res);
	res--;
	time_view();
	}
}

void time_view()
{
 struct timespec ts;
 timespec_get(&ts, TIME_UTC);
 char buff[100];
 strftime(buff, sizeof buff, "%D %T", gmtime(&ts.tv_sec));
 printf("Current time: %s.%09ld UTC\n", buff, ts.tv_nsec);
}

int main(int argc, char* argv[])
{
atexit(end);
int n=atoi(argv[1]);

struct timespec time;
time.tv_sec=0;
time.tv_nsec=9999;

for(int i=0; i<n; i++)
{
res++;
nanosleep(&time, NULL);
}
return 0;
}


