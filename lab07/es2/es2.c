#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define MAX_STR 256

//struct for thread parameters
typedef struct s_param
{
	char *inp_file;
	char *out_file;
} t_param;

//protype
void *thread_sort(void *param);
int int_cmp(const void * a, const void * b);

int main(int argc, char **argv)
{
	int n;			//number of files
	int i;			//iterator
	char strA[MAX_STR];	//strA = "file" for (file1.txt file2.txt ...)
	char strB[MAX_STR];	//strB = "out" for (out1.xt out2.txt ...)
	t_param *parameters;	//array of threads' parameters
	pthread_t *tid;		//array of threads id

	//get parameters
	if(argc< 4)
	{
		fprintf(stderr, "Parameters error!\n"
				"Usage: ./es2 <n> <strA> <strB>\n");
		return 1;
	}

	sscanf(argv[1], "%d", &n);
	strcpy(strA, argv[2]);
	strcpy(strB, argv[3]);

	//generate thread parameters and malloc tid array
	parameters = (t_param *) malloc(n * sizeof(t_param));
	for(i=0; i<n; i++)
	{
		parameters[i].inp_file = malloc((strlen(strA) + 6) * sizeof(char));
		sprintf(parameters[i].inp_file, "%s%d.txt", strA, i+1);

		parameters[i].out_file = malloc((strlen(strB) + 6) * sizeof(char));
		sprintf(parameters[i].out_file, "%s%d.txt", strB, i+1);
	}
	tid = (pthread_t *) malloc(n * sizeof(pthread_t));

	//generation of the n-threads
	for(i=0; i<n; i++)
	{
		if(pthread_create(&tid[i], NULL, thread_sort, (void *) &parameters[i]))
		{
			fprintf(stderr, "Can't create thread!\n");
			return 2;
		}
	}

	//wait all threads
	for(i=0; i<n; i++)
	{
		pthread_join(tid[i], NULL);
	}


	//free memory
	for(i=0; i<n; i++)
	{
		free(parameters[i].inp_file);
		free(parameters[i].out_file);
	}
	free(parameters);
	free(tid);

	return 0;
}

void *thread_sort(void *param)
{
	t_param *parameter = (t_param *) param;	//receive param.
	FILE *fp_in;				//file pointer of inp file
	FILE *fp_out;				//file pointer of out file
	int n;					//number of numbers
	int *v;					//array of numbers
	int i;					//for iterator

	//open inp file
	if((fp_in = fopen(parameter->inp_file, "r")) == NULL)
	{
		fprintf(stderr, "Can't open %s\n", parameter->inp_file);
		pthread_exit(NULL);
	}

	//create out file
	if((fp_out = fopen(parameter->out_file, "w")) == NULL)
	{
		fprintf(stderr, "Can't create %s\n", parameter->out_file);
		pthread_exit(NULL);
	}

	//read number of numbers and allocate a corrispondent int array
	fscanf(fp_in, "%d", &n);
	v = (int *) malloc(n * sizeof(int));
	
	//save numbers in the array
	for(i=0; i<n; i++)
	{
		fscanf(fp_in, "%d", &v[i]);
	}

	//sort
	qsort(v, n, sizeof(int), int_cmp);

	//write sorted array into out file
	for(i=0; i<n; i++)
	{
		fprintf(fp_out, "%d\n", v[i]);
	}

	//close files and free memory
	free(v);
	fclose(fp_in);
	fclose(fp_out);

	pthread_exit(NULL);
}

int int_cmp(const void * a, const void * b)
{
	   return ( *(int*)a - *(int*)b );
}
