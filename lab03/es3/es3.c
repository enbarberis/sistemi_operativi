#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void print_error(const char *msg, int exit_value);
void P368();
void P2457();

int main(int argc, char **argv)
{
	pid_t pid;

	printf("P01 - %d\n", getpid());

	pid = fork();

    	if(pid < 0)
    	{
        	print_error("Can't fork #1", -1);
    	}
	else if(!pid)
	{
		//child process
		P368();
	}
	else
	{
		//father process
		P2457();

		waitpid(pid, (int *)0, 0);
		printf("P09 - %d\n", getpid());
	}

        
    return 0;
}


void P368()
{
	pid_t pid;

	printf("P03 - %d\n", getpid());
	
	pid = fork();

	if(pid < 0)
	{
		print_error("Can't fork #2", -2);
	}
	if(!pid)
	{
		printf("P06 - %d\n", getpid());
		exit(0);
	}
	else
	{
		waitpid(pid, (int *)0, 0);
		printf("P08 - %d\n", getpid());
	}
}

void P2457()
{
	pid_t pid;

	printf("P02 - %d\n", getpid());
	
	pid = fork();

	if(pid < 0)
	{
		print_error("Can't fork #3", -3);
	}
	if(!pid)
	{
		printf("P05 - %d\n", getpid());
		exit(0);
	}
	else
	{
		printf("P04 - %d\n", getpid());
		waitpid(pid, (int *)0, 0);
	}

	printf("P07 - %d\n", getpid());

}

void print_error(const char *msg, int exit_value)
{
    fprintf(stderr, "%s\n", msg);
    exit(exit_value);
}

