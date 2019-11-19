#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
int licz =0;

void endfunc(int num, void* toclose)
{

  printf("%i\n",*((int*)toclose));
    printf("[%i]\n",num);
}

int main(int argc, char** argv)
{
  int* tab = (int*)malloc(10*sizeof(int));
  for (int i=0;i<10;i++)tab[i] = i;
  for (int i=0;i<10;i++) on_exit(endfunc,&tab[i]);
  return 0;
}
