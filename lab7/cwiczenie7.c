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
	char c;
	float size = 10;
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
				return -10;
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


fd_in=open(argv[optind],O_RDONLY); //RONLY??
if (fd_in==-1)
{
	printf("error opening file");
	return -11;
}
printf("In: %d \n", fd_in);

if (argc-optind==2)
{
fd_out=open(argv[optind+1],O_WRONLY);

        if (fd_out==-1)
        {
                printf("Error with output file");
                return -12;
        }
printf("Out: %d \n", fd_out);
}



//######################
if(tryb==1)
{
if (argc-optind==2) //jeśli podany plik wynikowy
{
        fd_out=open(argv[optind+1],O_WRONLY);

        if (fd_out==-1)
	{
                printf("Error with output file");
                return -12;
        }
	char* buf = (char*)calloc(1,sizeof(char));
	int i=0; //pozycja w wyjściowym pliku	
	int licznik=0;
	while(1)	
	{
		int j=0;
		char* buf2= (char*)calloc(size,sizeof(char));
		lseek(fd_out,licznik*size, SEEK_SET);
		while (j<size)
		{
			lseek(fd_in,i,SEEK_SET);
			read(fd_in, buf, 1);
			if (buf[0]=='\n')
			{
				i++;
				j++;
				break;
			}
			else
			{
			strcat(buf2,buf);	
			//printf("Lseek: %s \n", buf);
			i++;
			j++;
			}
		}
	licznik++;
	write(fd_out, buf2,size); //wsadzic do pliku	
	free(buf2);
	if (read(fd_in, buf,1)==0) // warunek przerwania
        break; //warunek wyjscia z pętli
	}
}
}
if(tryb==2)
{
//xd
}
return 0;
}
