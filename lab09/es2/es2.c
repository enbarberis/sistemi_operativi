#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#define MAX_RANDOM_SLEEP 5
#define N_THREAD	8

void random_sleep();			//sleep for a random time
void *thread_A(void *param);
void *thread_B(void *param);
void *thread_C(void *param);
void *thread_DH(void *param);
void *thread_E(void *param);
void *thread_F(void *param);
void *thread_G(void *param);
void *thread_I(void *param);

//semaphore
sem_t *sem_BCD;
sem_t *sem_EF;
sem_t *sem_G;
sem_t *sem_I;

int main(int argc, char **argv)
{
	pthread_t tid[N_THREAD];	//tid array of A to I thread
	int i;				//iterator

	//semaphore malloc
	sem_BCD = (sem_t *) malloc(sizeof(sem_t));
	sem_EF = (sem_t *) malloc(sizeof(sem_t));
	sem_G = (sem_t *) malloc(sizeof(sem_t));
	sem_I = (sem_t *) malloc(sizeof(sem_t));

	//semaphore init
	sem_init(sem_BCD, 0, 0);
	sem_init(sem_EF, 0, 0);
	sem_init(sem_G, 0, 0);
	sem_init(sem_I, 0, 0);
	
	while(1)
	{
		printf("\n\nNEW LOOP\n");

		//thread creation
		i = 0;
		pthread_create(&tid[i++], NULL, thread_A, NULL);
		pthread_create(&tid[i++], NULL, thread_B, NULL);
		pthread_create(&tid[i++], NULL, thread_C, NULL);
		pthread_create(&tid[i++], NULL, thread_DH, NULL);
		pthread_create(&tid[i++], NULL, thread_E, NULL);
		pthread_create(&tid[i++], NULL, thread_F, NULL);
		pthread_create(&tid[i++], NULL, thread_G, NULL);
		pthread_create(&tid[i++], NULL, thread_I, NULL);
		
		random_sleep();
	
		//wait thread destruction
		for(i=0; i<N_THREAD; i++)
		{
			pthread_join(tid[i], NULL);	
		}
		
		random_sleep();
	}

	return 0;
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

void *thread_A(void *param)
{
	random_sleep();
	printf("A\n");

	sem_post(sem_BCD);
	sem_post(sem_BCD);
	sem_post(sem_BCD);

	random_sleep();
	pthread_exit(NULL);
}


void *thread_B(void *param)
{
	random_sleep();

	sem_wait(sem_BCD);
	printf("B\n");
	sem_post(sem_I);

	random_sleep();
	pthread_exit(NULL);
}


void *thread_C(void *param)
{
	random_sleep();
	
	sem_wait(sem_BCD);
	printf("C\n");
	sem_post(sem_EF);
	sem_post(sem_EF);

	random_sleep();
	pthread_exit(NULL);
}


void *thread_DH(void *param)
{
	random_sleep();
	
	sem_wait(sem_BCD);
	printf("D\n");
	printf("H\n");
	sem_post(sem_I);

	random_sleep();
	pthread_exit(NULL);
}


void *thread_E(void *param)
{
	random_sleep();

	sem_wait(sem_EF);
	printf("E\n");
	sem_post(sem_G);

	random_sleep();
	pthread_exit(NULL);
}


void *thread_F(void *param)
{
	random_sleep();
	
	sem_wait(sem_EF);
	printf("F\n");
	sem_post(sem_G);

	random_sleep();
	pthread_exit(NULL);
}


void *thread_G(void *param)
{
	random_sleep();
	
	sem_wait(sem_G);
	sem_wait(sem_G);
	printf("G\n");
	sem_post(sem_I);

	random_sleep();
	pthread_exit(NULL);
}

void *thread_I(void *param)
{
	random_sleep();
	
	sem_wait(sem_I);
	sem_wait(sem_I);
	sem_wait(sem_I);
	printf("I\n");

	random_sleep();
	pthread_exit(NULL);
}
