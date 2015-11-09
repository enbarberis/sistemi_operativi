#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <ctype.h>

#define PID_FILE_CHILD_1 "pid_child_1.txt"
#define PID_FILE_CHILD_2 "pid_child_2.txt"
#define STRINGS_FILE "strings.txt"
#define MAX_STR 256
#define END_STR "end"
#define END_STR_UPPER "END"

void to_upper(char *str);
static void sigusr1(int sig_num);
static void sigusr2(int sig_num);

int main(int argc, char **argv)
{
	int pid;

	//reset pid files and char file
	fopen(PID_FILE_CHILD_1, "w");
	fopen(PID_FILE_CHILD_2, "w");
	fopen(STRINGS_FILE, "w");
	
	pid = fork();

	if(pid < 0)
	{
		fprintf(stderr, "Can't fork!\n");
		return 1;
	}
	else if(!pid)
	{
		//==== CHILD 1 ====
		
		FILE *fp;
		int brother_pid;
		char str[MAX_STR];

		if(signal(SIGUSR2, sigusr2) == SIG_ERR)
		{
			fprintf(stderr, "Can't assign signal handler\n");
			return 2;
		}
		
		//write my pid on file
		if((fp = fopen(PID_FILE_CHILD_1, "w")) == NULL)
		{
			fprintf(stderr, "Can't create file\n");
			return 3;
		}
			
		fprintf(fp, "%d", getpid());

		fclose(fp);
		
		//read brother pid
		while((fp = fopen(PID_FILE_CHILD_2, "r")) == NULL)
		{
			sleep(1);
		}
		
		while(fscanf(fp, "%d", &brother_pid) != 1)
		{
			sleep(1);
		}

		fclose(fp);

		printf("[C1]My brother pid is %d\n", brother_pid);

		//read strings
		do
		{
			printf("String: ");

			scanf("%s", str);
			//strcpy(str, "CiAoOoOoO123");

			if((fp = fopen(STRINGS_FILE, "w")) == NULL)
			{	
				fprintf(stderr, "Can't create file\n");
				return 4;
			}

			fprintf(fp, "%s", str);

			fclose(fp);

			//send signal to brother to tell him to read
			kill(brother_pid, SIGUSR1);

			//wait brother to print uppercase str
			pause();

			printf("[C1] After pause\n");

		}while(strcmp(str, END_STR) != 0);

	}
	else
	{
		pid = fork();
		if(pid < 0)
		{
			fprintf(stderr, "Can't fork!\n");
			return 2;
		}
		else if(!pid)
		{
			//CHILD 2
			FILE *fp;
			int brother_pid;
			char str[MAX_STR];

			if(signal(SIGUSR1, sigusr1) == SIG_ERR)
			{
				fprintf(stderr, "Can't assign signal handler\n");
				return 5;
			}
		
			//write my pid on file
			if((fp = fopen(PID_FILE_CHILD_2, "w")) == NULL)
			{
				fprintf(stderr, "Can't create file\n");
				return 6;
			}

			fprintf(fp, "%d", getpid());

			fclose(fp);

			//read brother pid
			while((fp = fopen(PID_FILE_CHILD_1, "r")) == NULL)
			{
				sleep(1);
			}
		
			while(fscanf(fp, "%d", &brother_pid) != 1)
			{
				sleep(1);
			}

			fclose(fp);

			printf("[C2]My brother pid is %d\n", brother_pid);

			//read brother str and print it uppercased 
			do{
				//wait brother signal before read
				pause();

				printf("[C2] After pause\n");
			
				if((fp = fopen(STRINGS_FILE, "r")) == NULL)
				{
					fprintf(stderr, "Can't open file\n");
					return 5;
				}

				fscanf(fp, "%s", str);

				to_upper(str);

				fprintf(stdout, "%s\n", str);

				kill(brother_pid, SIGUSR2);
			
			}while(strcmp(str, END_STR_UPPER) != 0);
		}
	}
	

	return 0;
}

void to_upper(char *str)
{
	while(*str != '\0')
	{
		if(islower(*str))
		{
			*str = toupper(*str);
		}

		str++;
	}
}

static void sigusr1(int sig_num)
{
	//nothing
}


static void sigusr2(int sig_num)
{
	//nothing
}
