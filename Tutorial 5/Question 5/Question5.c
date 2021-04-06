#define _XOPEN_SOURCE 600 // required for barriers to work
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE
#define  _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <pthread.h>

int THREAD_COUNT=10;
int total_grade =0;
double total_bellcurve =0;
typedef struct Grade{
                
    int mark;
} Grade;
struct Grade *grades;
int i =0;
pthread_barrier_t mybarrier, bar;
pthread_mutex_t lock;

void *read_grades() 
{
	

	FILE *fp = fopen("grades.txt", "r");
	for ( i=0 ; i < 10 ; i++ )
	{
    fscanf(fp, "%d", &grades[i].mark);
	}
	fclose(fp);
	

	pthread_barrier_wait(&mybarrier);
	
	pthread_exit(0);
}

void save_bellcurve(int mark)
{	
	
	pthread_mutex_lock(&lock);
    total_grade += mark;
	total_bellcurve += 1.50*mark;
    FILE *f = fopen("bellcurve.txt" , "a");
    fprintf(f, "Bell Curved Grade = %lf\n", 1.50*mark);
	fclose(f);
    pthread_mutex_unlock(&lock);
	pthread_barrier_wait(&bar);
	
	pthread_exit(0);

}

// Main //
int main(void)
{
	int id;
	double mean=0;
    grades = (Grade *)malloc(10*sizeof(Grade));
	pthread_t ids[THREAD_COUNT];
	pthread_attr_t attr[THREAD_COUNT];
	pthread_barrier_init(&mybarrier, NULL,  1);
	pthread_barrier_init(&bar, NULL,  THREAD_COUNT);
	pthread_attr_init(&attr[0]);
	
	
	pthread_create(&ids[0], &attr[0], read_grades, NULL);
	pthread_join(ids[0], 0);

	for(int i=0;i<THREAD_COUNT;i++){
        pthread_attr_init(&attr[i]);
    }
	for (id = 0; id < THREAD_COUNT; id++)
	{  
		pthread_create(&ids[id], &attr[id], save_bellcurve, grades[id].mark);
	}
	
	for (id = 0; id < THREAD_COUNT; id++)
	{
		pthread_join(ids[id], 0);
	}


	printf("Total Grade is: %d \n", total_grade);
	mean=total_grade;
	mean=mean/10;
	printf("Mean before curve is: %lf \n", mean);
	mean=0;
	mean=total_bellcurve/10;
	printf("Mean after curve is: %lf \n", mean);
	free(grades);


	pthread_barrier_destroy(&mybarrier);
	pthread_barrier_destroy(&bar);
	pthread_mutex_destroy(&lock);
	return(0);
	
}