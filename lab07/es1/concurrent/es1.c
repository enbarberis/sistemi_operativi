#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char **argv)
{
	int n;
	int *v;
	int i;
	int pid;

	//read parameter
	if(argc < 2)
	{
		fprintf(stderr, "Parameters error!\nUsage: ./es1 <n>\n");
		return 1;
	}

	sscanf(argv[1], "%d", &n);

	
	//allocate array
	v = (int *) malloc(n * sizeof(int));
	if(v == NULL)
	{
		fprintf(stderr, "Can't malloc!\n");
		return 2;
	}


	//create a binary tree of fork
	for(i=0; i<n; i++)
	{
		pid = fork();
		
		if(pid < 0)
		{
			fprintf(stderr, "Can't fork!\n");
			return 3;
		}
		else if(!pid)
		{
			//CHILD
			v[i] = 1;
		}
		else
		{
			//FATHER
			v[i] = 0;
		}
	}

	printf("[%d]: ", getpid());
	for(i=0; i<n; i++)
	{
		printf("%d", v[i]);
	}

	printf("\n");

	if(pid > 0)
	{
		waitpid(pid, (int *)0, 0);
	}
	
	return 0;
}
