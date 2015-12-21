#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <wait.h>
#define MAX_RANDOM_SLEEP 7

void random_sleep();			//sleep for a random time
void sem_init(int *sem);			//semaphore initialization
void sem_signal(int *sem);			//semaphore signal
void sem_wait(int *sem);			//semaphore wait

int main(int argc, char **argv)
{
	int sem_CDH[2];
	int sem_I[2];
	int sem_EF[2];
	int sem_G[2];
	int pid;

	//semaphore init
	sem_init(sem_CDH);
	sem_init(sem_I);
	sem_init(sem_EF);
	sem_init(sem_G);

	while(1)
	{
		//external loop
		pid = fork();
		if(pid > 0)
		{
			//AB
			random_sleep();
			
			printf("A\n");
			sem_signal(sem_CDH);
			sem_signal(sem_CDH);
			printf("B\n");
			sem_signal(sem_I);

			waitpid(pid, (int *)0, 0);
		}
		else
		{
			pid = fork();
			if(pid > 0)
			{
				//C
				random_sleep();

				sem_wait(sem_CDH);
				printf("C\n");
				sem_signal(sem_EF);
				sem_signal(sem_EF);

				waitpid(pid, (int *)0, 0);
				exit(0);
			}
			else
			{
				pid = fork();
				if(pid > 0)
				{
					//DH
					random_sleep();

					sem_wait(sem_CDH);
					printf("D\n");
					printf("H\n");
					sem_signal(sem_I);

					waitpid(pid, (int *)0, 0);
					exit(0);
				}
				else
				{
					pid = fork();
					if(pid > 0)
					{
						//E
						random_sleep();
						
						sem_wait(sem_EF);
						printf("E\n");
						sem_signal(sem_G);

						waitpid(pid, (int *)0, 0);
						exit(0);
					}
					else
					{
						pid = fork();
						if(pid > 0)
						{
							//F
							random_sleep();

							sem_wait(sem_EF);
							printf("F\n");
							sem_signal(sem_G);

							waitpid(pid, (int *)0, 0);
							exit(0);
						}
						else
						{
							pid = fork();
							if(pid > 0)
							{
								//G
								random_sleep();

								sem_wait(sem_G);
								sem_wait(sem_G);
								printf("G\n");
								sem_signal(sem_I);

								waitpid(pid, (int *)0, 0);
								exit(0);
							}
							else
							{
								//I
								random_sleep();

								sem_wait(sem_I);
								sem_wait(sem_I);
								sem_wait(sem_I);
								printf("I\n");

								exit(0);
							}
						}
					}
				}
			}
		}
	
		printf("\nNEW LOOP\n");
	
	}


	return 0;
}

void sem_init(int *sem)
{
	if(pipe(sem) == -1)
	{
		fprintf(stderr, "Can't create semaphore!\n");
		exit(1);
	}
}

void sem_signal(int *sem)
{
	char signal = 'K';
	
	if(write(sem[1], &signal, sizeof(char)) != 1)
	{
		fprintf(stderr, "Can't send signal!\n");
		exit(2);
	}
}

void sem_wait(int *sem)
{
	char signal;

	if(read(sem[0], &signal, sizeof(char)) != 1)
	{
		fprintf(stderr, "Failed wait!\n");
		exit(3);
	}
}

void random_sleep()
{
	int sec;
	
	//generate random number
	srand(getpid() + time(NULL));
	sec = (rand() % (MAX_RANDOM_SLEEP + 1));

	//printf("Going to sleep %d\n", sec);

	//sleep for sec seconds
	sleep(sec);
}	
