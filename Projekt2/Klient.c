#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


define FI "./FI"
define FO "./FO"

int FI_fd;
int FO_fd;

int main(int argc, char* argv[])
{
    FI_fd=open(FI, O_WRONLY);
    if (FI_fd==-1)
    {
        perror("Opening FI\n");
        return -2;
    }
    printf("Fi opened\n");
    
    
    FO_fd=open(FI, O_RDONLY);
    if (FO_fd==-1)
    {
        perror("Opening FO\n");
        return -2;
    }
    printf("Fo opened\n");
}
