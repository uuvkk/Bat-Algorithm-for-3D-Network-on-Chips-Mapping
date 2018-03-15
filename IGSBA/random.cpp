#include <stdio.h>
#include <sys/time.h>
#include <fcntl.h>
#include <stdlib.h>//rand
#include <unistd.h>//read,close

void init_random ()
{
  unsigned int ticks;
  struct timeval tv;
  int fd;
  gettimeofday (&tv, NULL);
  ticks = tv.tv_sec + tv.tv_usec;
  fd = open ("/dev/urandom", O_RDONLY);
  if (fd > 0)
  {
    unsigned int r;
    int i;
    for (i = 0; i < 512; i++)
    {
      read (fd, &r, sizeof (r));
      ticks += r;
    }
    close (fd);
  }

  srand (ticks);
  //printf("init finished ");
}

unsigned int new_rand ()
{
  int fd;
  unsigned int n = 0;
  fd = open ("/dev/urandom", O_RDONLY);
  if (fd > 0)
  {
    read (fd, &n, sizeof (n));
  }
  close (fd);
  return n;
}

/*
int main ()
{
  int  i;
  init_random ();
  //n = rand ();
  //printf ("n=%d ", n);
  int a=0,a1=0,a2=0,a3=0,a4=0,a5=0,a6=0,a7=0,a8=0,a9=0,a10=0,a11=0,a12=0;
  for(i=0; i<10000; i++)
  {
    int x=new_rand()%13;
    switch(x)
    {
      case 0: a++; break;
      case 1: a1++; break;
      case 2: a2++; break;
      case 3: a3++; break;
      case 4: a4++; break;
      case 5: a5++; break;
      case 6: a6++; break;
      case 7: a7++; break;
      case 8: a8++; break;
      case 9: a9++; break;
      case 10: a10++; break;
      case 11: a11++; break;
      case 12: a12++; break;
    }
  }
  printf("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",a,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12);
}
*/
