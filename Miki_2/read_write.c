#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>


void get_args(char** out, char** in, int* noBytes, int* subst_s, int* subst_p,int* subst_t,int* argc, char** argv[], int* err, int *trunc, int* position)
{
int opt;
	while ((opt=getopt(*argc, *argv, "o:i:n:p:t:s")) != -1)
	{
	switch (opt)
		{
		case 'o':
			*out=optarg;
			break;
		case 'i':
			*in=optarg;
        	        break;

		case 'n':
			*err=0;
			*noBytes=strtol(optarg, NULL, 10);
	                break;

		case 's':
			*subst_s=1;
               		break;
		
	       	case 'p':
                        *subst_p=1;
			*position=strtol(optarg, NULL, 10);
                        break;
		
		case 't':
			*subst_t=1;
			*trunc=strtol(optarg, NULL, 10);
                        break;

		default: 
                printf ("You get wrong arguments, noob!");
		exit(EXIT_FAILURE);

		}
	}

}

int main(int argc, char* argv[])
{

	if (argc<3)
	{
	printf ("Wrong numbers of arguments");
	return 1;
	}


char* out ="\0"; //wskaźnik na string, nazwę pliku wyjściowego
char* in ="\0"; //wejściowego
int noBytes = 0; //liczba bajtów do przekopiowania
int subst_s = 0; //sprawdza, czy zamieniać, czy nie, a dokładniej czy dany parametr występuje
int subst_p = 0;
int subst_t = 0;
int err=1;
int trunc=0;
int position=0;

get_args(&out, &in, &noBytes, &subst_s, &subst_p, &subst_t, &argc, &argv, &err, &trunc, &position); //pobranie argumentów
//printf("input: %s\t output: %s\t noBytes: %d\n", in, out, noBytes);

//open returns file descriptors jak chuj!!

if (err)
{
printf("Missing n argument!");
exit(1);
}
	
int fd1=open(in, O_RDONLY, 0); // tworze deskryptory
int fd2;

if (subst_s)
	{
                fd2 = open(out, O_CREAT|O_WRONLY, 0666); //tylko zapis
        }
        else {
                fd2 = open(out, O_CREAT |O_WRONLY | O_TRUNC, 0666); //wydupc wszystko i zapisz nowe
        }


char* c = (char*)calloc(100,sizeof(char)); //tu tworzę jakiś bufor, do którego wdupcam dane
read(fd1, c, noBytes); //wczytanie do bufora
printf("%s", c);

if (subst_p)
{
	lseek(fd2,position,SEEK_SET);
}

write (fd2, c, noBytes); //wczytanie do nowego pliku z bufora, de facto kopiowanie
if (subst_t)
{
ftruncate(fd2, trunc);
}
  if(close(fd1) < 0)
        {
                perror("c1");
                exit(1);
        }
        if(close(fd2) < 0)
        {
                perror("c2");
                exit(1);
        }

        return 0;
	////////
}
