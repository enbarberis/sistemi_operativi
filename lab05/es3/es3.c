#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	int pid = fork();

	if(pid < 0)
	{
		fprintf(stderr, "Can't fork!\n");
		return 1;
	}
	else if(!pid)
	{
		//child process
		while(1)
		{
			printf("Child is waiting...\n");
			pause();
			printf("Child Woke-up\n");
			sleep(2);
			kill(getppid(), SIGUSR2);
		}
	}
	else
	{
		//father process
		while(1)
		{
			sleep(2);
			kill(pid, SIGUSR1);
			printf("Father is waiting...\n");
			pause();
			printf("Father Woke-up\n");
		}
	}

	return 0;
}


/*
static void sigusr1(int sig_num)
{
	if(sig_num == SIGUSR1)
	{
		printf("Child Woke-up (Received SIGUSR1)\n");
	}
	else
	{
		printf("Received wrong signal!\n");
	}

	sleep(2);


}
static void sigusr2(int sig_num)
{
	
}
*/

/*
 	if(signal(SIGUSR1, sigusr1) == SIG_ERR || signal(SIGUSR2, sigusr2) == SIG_ERR)
	{
		fprintf(stderr, "Can't set signal handler!\n");
		return 1;
	}

	while(1);

 */
