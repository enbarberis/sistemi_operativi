#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>

#define MAX_BUF 256
#define MAX_EXEC_PAR 128
#define MAX_SYS_PAR 1024
#define DELIMITER "end"
#define SYS_MODE  '1'
#define EXEC_MODE '2'

void free_exec_param(char **exec_parameters, int n);

int main(int argc, char **argv)
{
	FILE *fp;				//file pointer
	char buffer[MAX_BUF];			//buffer to read single word
	char *exec_parameters[MAX_EXEC_PAR];	//parameters array for exec
	char sys_parameters[MAX_SYS_PAR];	//parameters string for system
	int i = 0;				//parameters counter
	int pid;				//fork return value

	if(argc < 3)
	{
		fprintf(stderr, "Parameters error!\n"
				"Usage: ./es3 <inp_file> <mode>\n"
				"mode = 1 execute with system\n"
				"mode = 2 execute with exec\n");
		return -1;
	}

	if((fp = fopen(argv[1], "r")) == NULL)
	{
		fprintf(stderr, "Can't open file %s\n", argv[1]);
		return -2;
	}

	sys_parameters[0] = '\0'; 	//reset string

	while(fscanf(fp, "%s", buffer) != EOF)
	{
		if(strcmp(buffer, DELIMITER) == 0)
		{
			//if I read "end"

			if(argv[2][0] == EXEC_MODE)
			{
				//if exec mode
				exec_parameters[i] = (char *) 0;			
				
				pid = fork();
				
				if(pid == -1)
				{
					fprintf(stderr, "Can't fork!\n");
					return -1;
				}
				else if(!pid)
				{
					//only child execute the exec and then die
					execvp(exec_parameters[0], exec_parameters);
					//execvp(executable file name, argv); 
				}
				else
				{
					//father wait child and sleep 3 seconds
					waitpid(pid, (int *)0, 0);
					sleep(3);

					//free and reset exec_param
					free_exec_param(exec_parameters, i);
					i = 0;
				}
			}

			if(argv[2][0] == SYS_MODE)
			{
				//if it's sys mode
				printf("=====EXECUTIN %s=====\n", sys_parameters);
				system(sys_parameters);
				sys_parameters[0] = '\0';
			}
		}
		else
		{
			if(argv[2][0] == EXEC_MODE)
			{
				//save param. as array for exec
				exec_parameters[i] = (char *) malloc(sizeof(char) * strlen(buffer));
				strcpy(exec_parameters[i], buffer);
				i++;
			}
			if(argv[2][0] == SYS_MODE)
			{
				//save param as string for system
				strncat(sys_parameters, buffer, MAX_SYS_PAR - strlen(sys_parameters));
				strncat(sys_parameters, " ", MAX_SYS_PAR - strlen(sys_parameters));
			}
		}
	}

	return 0;
}

void free_exec_param(char **exec_parameters, int n)
{
	int i;

	for(i=0; i<n; i++)
	{
		free(exec_parameters[i]);
	}
}
