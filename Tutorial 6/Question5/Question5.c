#define _XOPEN_SOURCE 700 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


int THREAD_COUNT=5;
int total_sum=0;
sem_t factsum;



void factorial(int number)
{
    sem_wait(&factsum);
    int factorl=1;
    int idf=1;

    if (number == 0)
    {
        factorl=1;
    }
    else
    {
        for (idf=1; idf <= number; ++idf)
        {
            factorl *= idf;
        }
    }

total_sum += factorl;

printf("Calculated factorial is: %d \n", factorl);
printf("Current total sum is: %d \n", total_sum);

sem_post(&factsum);

return 0;
}

int main()
{
int i=0;
int numbers[THREAD_COUNT];
pid_t pid;

sem_init(&factsum, 0, 1);

printf("Please Enter 5 integer Numbers: \n");
FILE *f1 = fopen("numbers.txt" , "w");

for (i=0; i<THREAD_COUNT; i++){
printf("Please Enter Number %d:", i+1);
scanf("%d", &numbers[i]);
fprintf(f1, "%d\n", numbers[i]);

}

fclose(f1);

pid = fork();
if (pid == 0)
{ /* child process */
    int i=0;
    int numberstemp[THREAD_COUNT];
    pthread_t ids[THREAD_COUNT];
    pthread_attr_t attr[THREAD_COUNT];

    for(int i=0;i<THREAD_COUNT;i++)
    {
		pthread_attr_init(&attr[i]);
    }

    FILE *f2 = fopen("numbers.txt" , "r");

    for ( i=0 ; i < THREAD_COUNT ; i++ )
	{
        fscanf(f2, "%d", &numberstemp[i]);
        pthread_create(&ids[i], &attr[i], factorial, numberstemp[i]);
	}

	fclose(f2);
    i=0;
    for (i = 0; i < THREAD_COUNT; i++)
	{
		pthread_join(ids[i], 0);
	}
	FILE *f3 = fopen("sum.txt" , "w");
    fprintf(f3, "%d\n", total_sum);
    fclose(f3);
}
else
{
wait(NULL);

FILE *f4 = fopen("sum.txt" , "r");
fscanf(f4, "%d", &i);
printf("Total sum after child is terminated is %d\n", i);
fclose(f4);
}

sem_destroy(&factsum);
return 0;
}
