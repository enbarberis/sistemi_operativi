#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void print_error(char *msg, int exit_value);
void create_children(int n);

void create_children(int n)
{
	if(n > 0)
	{
		printf("[%d]I'm father, and I'm going to generate 2 children\n", getpid());

		int pid1 = fork();
		
		if(pid1 < 0)
		{
			print_error("Can't fork", -1);
		}
		else if(!pid1)
		{
			//first child
			printf("[%d -> %d]I'm first child\n", getppid(), getpid());
			create_children(n-1);
		}
		else
		{
			//father fork
			int pid2 = fork();
			if(!pid2 < 0)
			{
				print_error("Can't fork!\n", -2);			
			}
			else if(!pid2)
			{
				printf("[%d -> %d]I'm second child\n", getppid(), getpid());
				create_children(n-1);
			}
			else
			{
				//father dies
				printf("[%d]I'm father and I'm dying\n", getpid());
				exit(0);
			}
		}
	}
}

int main(int argc, char **argv)
{
	int n;
	int t;

	setbuf(stdout, 0);

	if(argc < 3)
	{
		print_error("Parameters error!\nUsage: ./es2 <n> <t>\n", -1);
	}

	sscanf(argv[1], "%d", &n);
	sscanf(argv[2], "%d", &t);

	create_children(n);

	printf("[%d -> %d]I'm leaf process\n", getppid(), getpid());

	sleep(t);

	return 0;
}


void print_error(char *msg, int exit_value)
{
	fprintf(stderr, "%s\n", msg);
	exit(exit_value);
}

