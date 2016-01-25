#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 3
#define DETACH_T 1

void *BusyWork(void *null)
{
   int i;
   double result=0.0;

   for (i=0; i<1000000; i++)  {
     result = result + (double)random();
   }

   printf("Thread result = %e\n",result);

   pthread_exit ((void *) 0);
}

int main (
  int argc,
  char *argv[]
  )
{
  pthread_t thread[NUM_THREADS];
  pthread_attr_t attr;
  int rc, t;
  void *status;

#if DETACH_T
  /* Initialize and set thread detached attribute */
  pthread_attr_init (&attr);
  pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_JOINABLE);
#endif

  for (t=0; t<NUM_THREADS; t++) {
    printf ("Creating thread %d\n", t);
#if DETACH_T
    rc = pthread_create (&thread[t], &attr, BusyWork, NULL); 
#else
    rc = pthread_create (&thread[t], NULL, BusyWork, NULL); 
#endif
    if (rc) {
      printf("ERROR; return code from pthread_create() is %d\n", rc);
       exit(-1);
    }
  }

#if 0
  /* Free attribute */
  pthread_attr_destroy (&attr);
#endif

  /* Wait for the threads */
  for (t=0; t<NUM_THREADS; t++) {
    rc = pthread_join (thread[t], &status);
    if (rc) {
      printf("ERROR return code from pthread_join() is %d\n", rc);
      exit(-1);
    }
    printf("Completed join with thread %d status= %ld\n",t,(long)status);
  }

  pthread_exit(NULL);
}

