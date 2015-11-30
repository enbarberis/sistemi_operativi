#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define MAX_STR 256

//struct for thread parameters
typedef struct s_param
{
	char *inp_file;		//input file
	int n;		 	//number of elements
	int *v;			//array of sorted numbers
} t_param;

//protoype
void *thread_sort(void *param);
int int_cmp(const void * a, const void * b);

int main(int argc, char **argv)
{
	FILE *fp_out;		//file pointer to output file
	int n;			//number of files
	int i,j,k,c;		//iterators
	char strA[MAX_STR];	//strA = "file" for (file1.txt file2.txt ...)
	t_param *parameters;	//array of threads' parameters
	pthread_t *tid;		//array of threads id
	int *old_merged_array;	//array to backup merged array
	int *new_merged_array;	//array to merge new fork array and old_merged_array
	int n_of_elements;	//number of elements of current merged array

	//get parameters
	if(argc< 4)
	{
		fprintf(stderr, "Parameters error!\n"
				"Usage: ./es2 <n> <strA> <file_out>\n");
		return 1;
	}

	sscanf(argv[1], "%d", &n);
	strcpy(strA, argv[2]);

	//generate thread parameters and malloc tid array
	parameters = (t_param *) malloc(n * sizeof(t_param));
	for(i=0; i<n; i++)
	{
		parameters[i].inp_file = malloc((strlen(strA) + 6) * sizeof(char));
		sprintf(parameters[i].inp_file, "%s%d.txt", strA, i+1);
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
	for(k=0; k<n; k++)
	{
		pthread_join(tid[k], NULL);

		if(k==0)
		{
			new_merged_array = parameters[k].v;
			n_of_elements = parameters[k].n;
		}
		else
		{
			old_merged_array = new_merged_array;
			new_merged_array = (int *) malloc((n_of_elements + parameters[k].n) * sizeof(int));

			//merge
			i = 0;	
			j = 0;
			c = 0;

			while(i < n_of_elements && j < parameters[k].n)
			{
				if(old_merged_array[i] < parameters[k].v[j])
				{
					new_merged_array[c] = old_merged_array[i++];
				}
				else
				{
					new_merged_array[c] = parameters[k].v[j++];
				}

				c++;
			}
	
			while(i < n_of_elements)
			{
				new_merged_array[c++] = old_merged_array[i++];
			}
			
			while(j < parameters[k].n)
			{
				new_merged_array[c++] = parameters[k].v[j++];				
			}

			n_of_elements += parameters[k].n;
			free(old_merged_array);
		}
	}

	//write merged and sorted array to output file
	if((fp_out = fopen(argv[3], "w")) == NULL)
	{
		fprintf(stderr, "Can't create output file\n");
		return 3;
	}

	for(i=0; i<n_of_elements; i++)
	{
		fprintf(fp_out, "%d\n", new_merged_array[i]);
	}

	fclose(fp_out);

	//free memory
	for(i=0; i<n; i++)
	{
		free(parameters[i].inp_file);
		if(i != 0)
			free(parameters[i].v);
	}
	free(new_merged_array);
	free(parameters);
	free(tid);

	return 0;
}

void *thread_sort(void *param)
{
	t_param *parameter = (t_param *) param;	//receive param.
	FILE *fp_in;				//file pointer of inp file
	int i;					//for iterator

	//open inp file
	if((fp_in = fopen(parameter->inp_file, "r")) == NULL)
	{
		fprintf(stderr, "Can't open %s\n", parameter->inp_file);
		pthread_exit(NULL);
	}

	//read number of numbers and allocate a corrispondent int array
	fscanf(fp_in, "%d", &(parameter->n));
	parameter->v = (int *) malloc(parameter->n * sizeof(int));
	
	//save numbers in the array
	for(i=0; i<parameter->n; i++)
	{
		fscanf(fp_in, "%d", &(parameter->v[i]));
	}

	//sort
	qsort(parameter->v, parameter->n, sizeof(int), int_cmp);

	fclose(fp_in);

	pthread_exit(NULL);
}

int int_cmp(const void * a, const void * b)
{
	   return ( *(int*)a - *(int*)b );
}
