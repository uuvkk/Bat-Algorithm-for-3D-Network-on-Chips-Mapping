//The randomization cites other people's work
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
