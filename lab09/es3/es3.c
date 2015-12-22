#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#define MAX_RANDOM_SLEEP 5
#define N_THREAD	9

void random_sleep();			//sleep for a random time
void *thread_A(void *param);		//threads function
void *thread_B(void *param);
void *thread_C(void *param);
void *thread_D(void *param);
void *thread_E(void *param);
void *thread_F(void *param);
void *thread_G(void *param);
void *thread_H(void *param);
void *thread_I(void *param);

//semaphore
sem_t *sem_A;
sem_t *sem_B;
sem_t *sem_C;
sem_t *sem_D;
sem_t *sem_E;
sem_t *sem_F;
sem_t *sem_G;
sem_t *sem_H;
sem_t *sem_I;

int main(int argc, char **argv)
{
	pthread_t tid[N_THREAD];	//tid array of A to I thread
	int i;				//iterator

	//semaphore malloc
	sem_A = (sem_t *) malloc(sizeof(sem_t));
	sem_B = (sem_t *) malloc(sizeof(sem_t));
	sem_C = (sem_t *) malloc(sizeof(sem_t));
	sem_D = (sem_t *) malloc(sizeof(sem_t));
	sem_E = (sem_t *) malloc(sizeof(sem_t));
	sem_F = (sem_t *) malloc(sizeof(sem_t));
	sem_G = (sem_t *) malloc(sizeof(sem_t));
	sem_H = (sem_t *) malloc(sizeof(sem_t));
	sem_I = (sem_t *) malloc(sizeof(sem_t));

	//semaphore init
	sem_init(sem_A, 0, 1);
	sem_init(sem_B, 0, 0);
	sem_init(sem_C, 0, 0);
	sem_init(sem_D, 0, 0);
	sem_init(sem_E, 0, 0);
	sem_init(sem_F, 0, 0);
	sem_init(sem_G, 0, 0);
	sem_init(sem_H, 0, 0);
	sem_init(sem_I, 0, 0);

	//thread creation
	i = 0;
	pthread_create(&tid[i++], NULL, thread_A, NULL);
	pthread_create(&tid[i++], NULL, thread_B, NULL);
	pthread_create(&tid[i++], NULL, thread_C, NULL);
	pthread_create(&tid[i++], NULL, thread_D, NULL);
	pthread_create(&tid[i++], NULL, thread_E, NULL);
	pthread_create(&tid[i++], NULL, thread_F, NULL);
	pthread_create(&tid[i++], NULL, thread_G, NULL);
	pthread_create(&tid[i++], NULL, thread_H, NULL);
	pthread_create(&tid[i++], NULL, thread_I, NULL);
		
	//threads never ends -> pthread_join is useless
	//pthread_join to not stop main thread
	pthread_join(tid[0], NULL);

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
	while(1)
	{
		sem_wait(sem_A);
	
		random_sleep();
		printf("A\n");
		random_sleep();

		sem_post(sem_B);
		sem_post(sem_C);
		sem_post(sem_D);
	}

	pthread_exit(NULL);
}

void *thread_B(void *param)
{
	while(1)
	{
		sem_wait(sem_B);
	
		random_sleep();
		printf("B\n");
		random_sleep();

		sem_post(sem_I);
	}

	pthread_exit(NULL);
}

void *thread_C(void *param)
{
	while(1)
	{
		sem_wait(sem_C);
	
		random_sleep();
		printf("C\n");
		random_sleep();

		sem_post(sem_E);
		sem_post(sem_F);
	}

	pthread_exit(NULL);
}

void *thread_D(void *param)
{
	while(1)
	{
		sem_wait(sem_D);
	
		random_sleep();
		printf("D\n");
		random_sleep();

		sem_post(sem_H);
	}

	pthread_exit(NULL);
}

void *thread_E(void *param)
{
	while(1)
	{
		sem_wait(sem_E);
	
		random_sleep();
		printf("E\n");
		random_sleep();

		sem_post(sem_G);
	}

	pthread_exit(NULL);
}

void *thread_F(void *param)
{
	while(1)
	{
		sem_wait(sem_F);
	
		random_sleep();
		printf("F\n");
		random_sleep();

		sem_post(sem_G);
	}

	pthread_exit(NULL);
}

void *thread_G(void *param)
{
	while(1)
	{
		sem_wait(sem_G);
		sem_wait(sem_G);
	
		random_sleep();
		printf("G\n");
		random_sleep();

		sem_post(sem_I);
	}

	pthread_exit(NULL);
}

void *thread_H(void *param)
{
	while(1)
	{
		sem_wait(sem_H);
	
		random_sleep();
		printf("H\n");
		random_sleep();

		sem_post(sem_I);
	}

	pthread_exit(NULL);
}

void *thread_I(void *param)
{
	while(1)
	{
		sem_wait(sem_I);
		sem_wait(sem_I);
		sem_wait(sem_I);
	
		random_sleep();
		printf("I\n\n\n");
		random_sleep();

		sem_post(sem_A);
	}

	pthread_exit(NULL);
}
