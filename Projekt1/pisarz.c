#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


int main(int argc, char* argv[])
{

int nr_fd;
int przesuniecie;
char * komunikat="\0";
int krotnosc=5;

int c;
while( (c = getopt(argc, argv, "N:")) != -1)
        {
                switch(c)
                {
                        case 'N':
                                krotnosc=strtol(optarg, NULL, 10);
                                break;
                        default:
                                printf("invalid flags, bye.\n");
                                return -10;
                }
        }
if (krotnosc < 0)
{
	printf("Wartość parametru N nie może być ujemna!");
	return -10;
}

if (!(argc-optind ==3) )
{
	printf("Błędna liczba parametrów\n");
	return -2;
}

nr_fd=strtol(argv[optind], NULL, 10);
przesuniecie=strtol(argv[optind+1], NULL, 10);
komunikat=argv[optind+2];

/*
printf("%d\n",nr_fd);
printf("%d\n",przesuniecie);
*/
printf("%s\n",komunikat);
//printf("%d\n\n\n", krotnosc);



int rozmiar= strlen(komunikat);
printf("%d\n", rozmiar);
lseek(nr_fd, przesuniecie, SEEK_SET);
write(nr_fd, komunikat, rozmiar);



return 0;
}
