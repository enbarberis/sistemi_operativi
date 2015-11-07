#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

static void sigusr1(int sig_num);
static void sigusr2(int sig_num);

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

		if(signal(SIGUSR1, sigusr1) == SIG_ERR)
		{
			fprintf(stderr, "Can't assign signal handler to SIGUSR1\n");
			exit(2);
		}

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

		if(signal(SIGUSR2, sigusr2) == SIG_ERR)
		{
			fprintf(stderr, "Can't assign signal handler to SIGUSR2\n");
			exit(2);
		}

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


static void sigusr1(int sig_num)
{
	if(sig_num == SIGUSR1)
	{
		printf("Received SIGUSR1\n");
	}
	else
	{
		printf("Received wrong signal!\n");
	}
}


static void sigusr2(int sig_num)
{
	if(sig_num == SIGUSR2)
	{
		printf("Received SIGUSR2\n");
	}
	else
	{
		printf("Received wrong signal!\n");
	}
}
