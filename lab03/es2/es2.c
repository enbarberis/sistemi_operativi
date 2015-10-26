#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void print_error(char *msg, int exit_value);

int main(int argc, char **argv)
{
	int n;		//per quante volte devo duplicare un processo
	int t;		//quanto deve attendere in secondi le foglie
	int i;		//var. per ciclo for

	if(argc < 3)
	{
		print_error("Parameters error!\nUsage: ./es1 <n> <t>\n", -1);
	}

	sscanf(argv[1], "%d", &n);
	sscanf(argv[2], "%d", &t);

	for(i=0; i<n; i++)
	{
		if(fork() < 0)
		{
			print_error("Can't fork\n", -2);
		}
		
		if(i == n-1)
		{
			sleep(t);
			printf("Process %d is terminated\n", getpid());
		}
	}

	return 0;
}


void print_error(char *msg, int exit_value)
{
	fprintf(stderr, "%s\n", msg);
	exit(exit_value);
}

