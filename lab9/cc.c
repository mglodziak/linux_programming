#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char* argv[])
{

int wiersz;
int kolumna;
char* str;
struct timespec ts={1,0};


if (argc < 2)
{
	printf("Wrong usage. Exiting");
	return -1;
}

char *c;
wiersz = strtol(argv[1], &c, 10);
c++;
kolumna=strtol(c, NULL, 10);
//timespecFromStr(argv[2], &ts);
str=(char*)malloc(strlen(argv[3]+1));
strcpy(str, argv[3]);
char* q=str;
printf("\x1b[H\x1b[J\n");
while (1)
{
	printf("\x1b[%d;%dH%c\n", wiersz, kolumna, *q++);
	if(*q=='\0')
		q=str;
	nanosleep(&ts, NULL);
	
}

return 0;
}
