#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <signal.h>

#define TIMER_SIG SIGHUP
#define CLOCK_ID CLOCK_REALTIME

/*
void thread_handler(union sigval sv) 
{
printf("dupa, co 5 sekund\n");
}
*/

static void handler(int signal);
int flaga = 0;

int main(int argc, char *argv[])
{

	char *file_dane = "\0";
	char *file_tablica = "\0";
	char *file_archiwum = "\0";
	int do_przekazania = 5;
	int c;

	int spr_d = 0;
	int spr_b = 0;
	int spr_l = 0;

	int fd_dane;
	int fd_tablica;
	int fd_archiwum;

	pid_t *dzieciaczki;
	struct sigaction sa;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = handler;
	if (sigaction(TIMER_SIG, &sa, NULL) == -1)
	{
		perror("signal");
		_exit(EXIT_FAILURE);
	}

	while ((c = getopt(argc, argv, "d:b:l:N:")) != -1)
	{
		switch (c)
		{
		case 'd':
			file_dane = optarg;
			spr_d = 1;
			break;
		case 'b':
			file_tablica = optarg;
			spr_b = 1;
			break;
		case 'l':
			file_archiwum = optarg;
			spr_l = 1;
			break;
		case 'N':
			do_przekazania = strtol(optarg, NULL, 10);
			break;
		default:
			printf("invalid flags, bye.\n");
			return -10;
		}
	}

	if (spr_d == 0 || spr_b == 0 || spr_l == 0)
	{
		printf("Parametry d, b, l są OBOWIĄZKOWE!\n");
		return -1;
	}

	fd_dane = open(file_dane, O_RDONLY, 0);
	if (fd_dane == -1)
	{
		printf("Plik z danymi musi istnieć!!\n");
		return -2;
	}

	fd_tablica = open(file_tablica, O_WRONLY | O_CREAT | O_EXCL, 0666);
	if (fd_tablica == -1)
	{
		printf("Coś poszło nie tak... fd_tablica. Prawdopodobnie plik już istnieje.\n");
		return -3;
	}

	fd_archiwum = open(file_archiwum, O_WRONLY | O_CREAT | O_EXCL, 0666);
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

	char *buf1 = (char *)calloc(1, sizeof(char));
	int licznik = 0;
	while (read(fd_dane, buf1, 1) != 0)
	{
		if (buf1[0] == '\n')
			licznik++;

		//printf("%s", buf1);
	}
	//printf("Licznik:%d \n", licznik);

	//char ** dane[licznik];

	int offsety[licznik + 1];
	offsety[0] = 0;

	char *buf = (char *)calloc(1, sizeof(char));
	int ix_dane = 0;
	int ix_offset = 1;
	lseek(fd_dane, 0, SEEK_SET);
	while (read(fd_dane, buf, 1) != 0)
	{
		if (buf[0] == '\n')
		{
			offsety[ix_offset] = ix_dane + 1;
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

	char *dane[licznik];
	ix_offset = 0;

	for (int i = 0; i < licznik; i++)
	{
		char *buf33 = (char *)calloc(offsety[ix_offset + 1] - offsety[ix_offset], sizeof(char));
		if (read(fd_dane, buf33, offsety[ix_offset + 1] - offsety[ix_offset]) == 0)
			break;
		dane[i] = buf33;
		ix_offset++;
	}
	//printf("%s\n", dane[1]);

	//for (int i =0; i< licznik; i++)
	//printf("%d\t%s\n",offsety[i],dane[i]);

	dzieciaczki = (pid_t *)malloc(sizeof(pid_t) * licznik);
	if (dzieciaczki == NULL)
	{
		printf("Blad alokacji pamieci\n");
		return -8;
	}

	for (int i = 0; i < licznik; i++)
	{
		switch (dzieciaczki[i] = fork())
		{
		case -1:
		{
			perror("fork\n");
			return -11;
		}
		case 0:

		{
			char str1[5];
			char str2[20];
			sprintf(str1, "%d", fd_tablica);
			sprintf(str2, "%d", offsety[i]);
			if (do_przekazania == 5)
				execl("pis", "pis", str1, str2, dane[i], NULL);
			else
			{
				char str3[8];
				sprintf(str3, "%d", do_przekazania);
				execl("pis", "pis", str1, str2, dane[i], "-N", str3, NULL);
			}
			break;
		}
		default:
			break;
		}
	}

	if (close(fd_tablica) < 0)
	{
		perror("tablica\n");
		return -4;
	}

	//	char *info = "5 seconds elapsed.";
	timer_t timerid;
	struct sigevent sev;
	struct itimerspec trigger;

	//        memset(&sev, 0, sizeof(struct sigevent));
	//        memset(&trigger, 0, sizeof(struct itimerspec));

	sev.sigev_notify = SIGEV_SIGNAL;
	sev.sigev_signo = TIMER_SIG;
	trigger.it_value.tv_sec = 0;
	trigger.it_value.tv_nsec = 675000000;
	trigger.it_interval.tv_sec = 0;
	trigger.it_interval.tv_nsec = 0;
	if (timer_create(CLOCK_ID, &sev, &timerid) < 0)
	{
		perror("timer_create");
		return -11;
	}

	for (int i = 1; i < licznik; i++)
	{
		setpgid(dzieciaczki[i], dzieciaczki[0]);
	}
	signal(SIGUSR1, SIG_IGN);

	for (int i = 0; i < 20; i++)
	{
		if (timer_settime(timerid, 0, &trigger, NULL))
		{
			perror("timer");
			return -12;
		}
		pause();
		if (flaga)
			kill(-getpgid(dzieciaczki[0]), SIGUSR1);

		else
		{
			int fd_tablica2;
			fd_tablica2 = open(file_tablica, O_RDONLY);
			if (fd_tablica2 == -1)
			{
				printf("Coś poszło nie tak... fd_tablica. Prawdopodobnie plik już istnieje.\n");
				return -3;
			}
			int wczytane;
			char *xx = (char *)malloc(1);
			if (xx == NULL)
			{
				printf("Alokacja pamięci leci w kulki\n");
				return -15;
			}
			while ((wczytane = read(fd_tablica2, xx, 1)) > 0)
			{
				//printf("-\n");
				write(fd_archiwum, xx, 1);
			}
			if (close(fd_tablica) < 0)
			{
				perror("tablica\n");
				return -4;
			}
		}
	}
	//       sleep(15);

	kill(-getpgid(dzieciaczki[0]), SIGTERM);

	if (close(fd_archiwum) < 0)
	{
		perror("archiwum\n");
		return -4;
	}

	if (close(fd_dane) < 0)
	{
		perror("tablica\n");
		return -4;
	}

	timer_delete(timerid);

	free(buf1);
	free(buf);

	return 0;
}

static void handler(int signal)
{

	if (flaga)
		flaga = 0;
	else
		flaga = 1;
}
