#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void print_error(char *msg, int exit_value);

void create_children(int n);

int main(int argc, char **argv)
{
	int n;
	int t;

	if(argc < 3)
	{
		print_error("Parameters error!\nUsage: ./es2 <n> <t>\n", -1);
	}

	sscanf(argv[1], "%d", &n);
	sscanf(argv[2], "%d", &t);

	create_children(n);

	printf("\t\t[%d->%d]I'm leaf process running\n", getppid(), getpid());
	sleep(t);

	return 0;
}


void create_children(int n)
{
	int pid1;
	int pid2;

	if(n > 0)
	{
		pid1 = fork();
		if(pid1 < 0)
		{
			print_error("Can't fork!\n", -2);
		}
		else if(!pid1)
		{
			//child
			printf("[%d->%d]I'm going to duplicate myself\n", getppid(), getpid());
			
			pid2 = fork();

			if(pid2 < 0)
			{
				print_error("Can't fork!\n", -3);
			}
			else if(!pid2)
			{
				//child of child	
				printf("[%d->%d]I'm child of child\n", getppid(), getpid());
				create_children(n-1);
			}
			else
			{
				//child
				printf("[%d->%d]I'm child\n", getppid(), getpid());
				create_children(n-1);
			}
		}
		else
		{
			//father
			printf("[%d->%d]I'm father and im going to die\n", getppid(), getpid());
			exit(0);
		}
	}

}

void print_error(char *msg, int exit_value)
{
	fprintf(stderr, "%s\n", msg);
	exit(exit_value);
}

