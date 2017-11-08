#include <stdio.h>
#include <stdlib.h>
#include <signal.h>


static void sighandler(int signo)
{
  if (signo == SIGUSR1)
    {
      printf("Parent Process: %d\n", getpid());
    }
  else
    {
      printf("Exited due to process %d\n", getpid());
      exit(1);
    }
}

int main()
{
  signal(SIGINT, sighandler);
  signal(SIGUSR1, sighandler);
  while(1)
    {
      printf("Forever loop, Process %d\n", getpid());
      sleep(1);
    }
  return 0;
}
