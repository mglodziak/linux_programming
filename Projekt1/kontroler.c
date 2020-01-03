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

char * file_dane="\0";
char * file_tablica="\0";
char * file_archiwum="\0";
int do_przekazania = 1;
int c;

int spr_d=0;
int spr_b=0;
int spr_l=0;

int fd_dane;
int fd_tablica;
int fd_archiwum;

while( (c = getopt(argc, argv, "d:b:l:N:")) != -1)
        {
                switch(c)
                {
                        case 'd':
                                file_dane=optarg;
				spr_d=1;
                                break;
                        case 'b':
                                file_tablica=optarg;
				spr_b=1;
				break;
 			case 'l':
                                file_archiwum=optarg;
				spr_l=1;
				break;
                        case 'N':
                                do_przekazania=strtol(optarg, NULL, 10);
				break;
                        default:
                                printf("invalid flags, bye.\n");
                                return -10;
                }
        }

if(spr_d==0 || spr_b==0 || spr_l==0)
{
	printf("Parametry d, b, l są OBOWIĄZKOWE!\n");
	return -1;
}

fd_dane=open(file_dane, O_RDONLY, 0);
if (fd_dane == -1)
{
	printf("Plik z danymi musi istnieć!!\n");
	return -2;
}

fd_tablica=open(file_tablica, O_WRONLY| O_CREAT | O_EXCL, 0666);
if (fd_tablica == -1)
{
	printf("Coś poszło nie tak... fd_tablica. Prawdopodobnie plik już istnieje.\n");
	return -3;
}

fd_archiwum=open(file_archiwum, O_CREAT | O_EXCL, 0666);
if (fd_archiwum == -1)
{
        printf("Coś poszło nie tak... fd_archiwum. Prawdopodobnie plik już istnieje.\n");
        return -3;
}
/*
printf("%s\n",file_dane); 
printf("%s\n",file_tablica);
printf("%s\n",file_archiwum);
printf("%d\n",do_przekazania);
*/

char* buf1=(char*)calloc(1, sizeof(char));
int licznik=0;
while(read(fd_dane, buf1, 1)!=0)
{
if (buf1[0]=='\n')
	licznik++;

//printf("%s", buf1);
}
//printf("Licznik:%d \n", licznik);
	
//char ** dane[licznik];

int offsety[licznik+1];
offsety[0]=0;



char* buf=(char*)calloc(1, sizeof(char));
int ix_dane=0;
int ix_offset=1;
lseek(fd_dane, 0, SEEK_SET);
while(read(fd_dane, buf, 1)!=0)
{
if(buf[0]=='\n')
{
	offsety[ix_offset]=ix_dane+1;
	ix_offset++;
	ix_dane++;
}
else
{
	ix_dane++;
}
}

//printf("\n\n");
//for (int j=0; j<licznik+1; j++)
//	printf("%d \n", offsety[j]);

lseek(fd_dane, 0, SEEK_SET);

char* dane[licznik];
ix_offset=0;

for (int i=0; i<licznik; i++)
{
char* buf33=(char*)calloc(offsety[ix_offset+1]-offsety[ix_offset], sizeof(char));
if (read(fd_dane, buf33, offsety[ix_offset+1]-offsety[ix_offset])==0)
	break;	
dane[i]=buf33;
ix_offset++;
}
//printf("%s\n", dane[1]);

//for (int i =0; i< licznik; i++)
//printf("%d\t%s\n",offsety[i],dane[i]);

for (int i=0; i<licznik; i++)
{
	if (!fork())
	{
		char str1[5];
		char str2[20];
		sprintf(str1, "%d", fd_tablica);
		sprintf(str2, "%d", offsety[i]);
		execl("pis","pis",str1, str2, dane[i] ,NULL);
	}
}


return 0;
}
