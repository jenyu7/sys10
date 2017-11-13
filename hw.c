/********
 * Jen Yu
 * Period 10 Systems
 * HW #10: Fire up the batSIGNAL
 * 2017-11-08
 ********/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

//Function to handle signals
static void sighandler(int signo)
{
  //Don't end the process if signal is SIGUSR1
	if (signo == SIGUSR1)
	{
		//print out the id of the parent process, but do not exit. 
		printf("Parent Process: %d\n", getpid());
	}
	//End the process if signal is SIGINT
	else if (signo == SIGINT)
	{
	  int fd = open("errlog", O_CREAT | O_WRONLY | O_APPEND, 0644 );
	  char msg[256] = "Exited process due to SIGINT error\n";
	  write(fd, msg, sizeof(msg));
	  close(fd);
	  //print out id of process exited, and reason being SIGINT
	  printf("Exited process %d due to SIGINT\n", getpid());
	  exit(1);
	}
}

//Question: Why does kill -30 <PID> result in the 'Power Failure' error?

int main()
{
	//Needs to account for two signals: SIGINT and SIGUSR1
	signal(SIGINT, sighandler);
	signal(SIGUSR1, sighandler);
	//Forever loop
	while(1)
    {
		printf("Forever loop: Process %d\n", getpid());
		sleep(1);
    }
	return 0;
}
