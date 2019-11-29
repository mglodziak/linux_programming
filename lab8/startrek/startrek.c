#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>

int flag = 0;

static void handler(int sig);
void draw(int hp);

int main(int argc, char* argv[])
{
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = handler;
 
    if(sigaction(SIGINT, &sa, NULL) == -1) //if error
    {
        perror("signal");
        _exit(EXIT_FAILURE);
    }

    srand(time(NULL));

    int def = 90;
    int hp = 10;

    draw(hp);
    printf("\n\n\n\nHP: %d\n\nWaiting for an attack (ctrl + c) ...\n",hp*10);

    while(1)
    {
        if(flag)
        {
            if(rand() % 100 > def)
            {
                hp--;
                def -= 10;
                if(!hp)
                {
                    printf("\x1b[H\x1b[J");
                    printf("Spring is coming!!\n");
                    abort(); 
                }  
                draw(hp);
                printf("\n\nAttack was successful :(\n\nHP: %d\n\nWaiting for an attack (ctrl + c) ...\n", hp*10);    
            }
            else
            {
                draw(hp);
                printf("\n\nYou've saved yourself!\n\nHP: %d\n\nWaiting for an attack (ctrl + c) ...\n",hp*10); 
            }
            flag = 0;
        }
    }
    exit(0);
}

static void handler(int sig)
{
    flag = 1;
}

void prt(int fd)
{
        if (fd==-1)
        {
                printf("error open file");
                exit(-1);
        }
        char* buf = (char*)calloc(2048,sizeof(char));
        if (read(fd,buf,2048)==0)
        {
                printf( "error read ");
                exit(-2);
        }

        printf("%s",buf);
        close(fd);

}

void draw(int hp)
{
system("clear");
int fd;
switch(hp)
{
	case 10:
		fd=open("snowman10.txt",O_RDONLY);
		prt(fd);
		break;
        case 9:
                fd=open("snowman9.txt",O_RDONLY);
                prt(fd);
                break;
        case 8:
                fd=open("snowman8.txt",O_RDONLY);
                prt(fd);
                break;
        case 7:
                fd=open("snowman7.txt",O_RDONLY);
                prt(fd);
                break;
        case 6:
                fd=open("snowman6.txt",O_RDONLY);
                prt(fd);
                break;
        case 5:
                fd=open("snowman5.txt",O_RDONLY);
                prt(fd);
                break;
        case 4:
                fd=open("snowman4.txt",O_RDONLY);
                prt(fd);
                break;
        case 3:
                fd=open("snowman3.txt",O_RDONLY);
                prt(fd);
                break;
        case 2:
                fd=open("snowman2.txt",O_RDONLY);
                prt(fd);
                break;
        case 1:
                fd=open("snowman1.txt",O_RDONLY);
                prt(fd);
                break;


}

}
