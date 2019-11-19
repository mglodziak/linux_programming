#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define BUF_SIZE 256

int main(int argc, char* argv[])
{
    char buf[BUF_SIZE];
    int fd = 68;
    if(argc == 1)
    {
        int flags;
        if((flags = fcntl(fd, F_GETFL)) == -1)
        {
            perror("descriptor");
            _exit(EXIT_FAILURE);
        }

        int accessMode = flags & O_ACCMODE;
        if(!(accessMode == O_RDONLY || accessMode == O_WRONLY))
        {
            perror("access mode");
            _exit(EXIT_FAILURE);
        }

        int numRead = read(fd, buf, BUF_SIZE);
        write(STDOUT_FILENO, buf, numRead);            
        write(STDOUT_FILENO, "\n", 1);

        if(close(fd) == -1)
        {
            perror("close\n");
            _exit(EXIT_FAILURE);
        }

        _exit(EXIT_SUCCESS);
    }
    else if(argc >= 2)
    {   
        pid_t child;
        int pipefd[2];
        if (pipe(pipefd) == -1) 
        {
            perror("pipe");
            _exit(EXIT_FAILURE);
        }

        switch(child = fork())
        {
            case -1:
                perror("fork");
                _exit(EXIT_FAILURE);

            case 0:
                {   
                    if (close(pipefd[1]) == -1) 
                    {
                        perror("close");
                        _exit(EXIT_FAILURE);
                    }

                    if ((pipefd[0] = dup2(pipefd[0], fd)) == -1)
                    {
                        perror("dup2");
                        _exit(EXIT_FAILURE);
                    }

                    argv[1] = argv[0];
				    execv(argv[1], argv+1);
				    break;
                }

            default:
                {
                    if(fcntl(fd, F_GETFL) == -1)
                    {
                        if (close(pipefd[0]) == -1) 
                        {
                            perror("close");
                            _exit(EXIT_FAILURE);
                        }

                        write(pipefd[1], argv[1], strlen(argv[1]));

                        if (close(pipefd[1]) == -1) 
                        {
                            perror("close");
                            _exit(EXIT_FAILURE);
                        }

                        _exit(EXIT_SUCCESS);    
                    }
                    else
                    {
                        int numRead = read(fd, buf, BUF_SIZE);
                        write(pipefd[1], buf, numRead);
                        write(pipefd[1], " ", 1);
                        write(pipefd[1], argv[1], strlen(argv[1]));

                        if (close(pipefd[0]) == -1) 
                        {
                            perror("close");
                            _exit(EXIT_FAILURE);
                        }

                        if (close(pipefd[1]) == -1) 
                        {
                            perror("close");
                            _exit(EXIT_FAILURE);
                        }

                        _exit(EXIT_SUCCESS);  
                    }
                }
            }
    }
}




/*
rodzic ma utworzyc N potomkow ( parametr)
komunikuje sie z nimi przez jeden wspolny potok. zostawai sobie czesc do czytania
a rodzic zostawai sobie czesc do zapisu.
rodzic w petli odczytuje z devurand float i rzuca do potoku.
potomek odczytuje liczbe float z potoku, sprawdza za pom fpclasify czy to float > 0
jezeli jest duzo wieksza to przycinamy
traktuje ta liczbe jako ilosc czasu do spania okreslona przez TIMEUNIT
jak nie jest okreslone to 3/8 sek.
Jezeli potomek odczyta liczeb <=0 albo nieprafidlowy float to umiera
oprocz wrzucania do potoku rodzic w sposob nie blokujacy patrzy czy jakies potomki
sie skonczyly i usuwa zombie z tablicy za bardzo nie obciazjac procesora */