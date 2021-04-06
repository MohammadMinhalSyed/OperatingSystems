#define _XOPEN_SOURCE 700 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int moving_sum[5]={0, 0, 0, 0, 0};
int THREAD_COUNT=5;

sem_t factsum;

typedef struct Factor{
    int index;
    int number
} Factor;


void factorial(struct Factor *factor){
sem_wait(&factsum);
int factorl=1;
int idf=1;

if (factor->number == 0)
{
    factorl=1;
}
else
{
    for (idf=1;idf<=factor->number;++idf)
    {
        factorl *= idf;
    }
}


if (factor->index > 0)
{
    moving_sum[factor->index] += moving_sum[factor->index -1] + factorl;
}

sem_post(&factsum);

if (factor->index > 1)
{
    sem_wait(&factsum);
    while (moving_sum[factor->index -1]<=0)
    {}
    sem_post(&factsum);
}

return 0;
}

int main()
{
int i=0;
struct Factor *factors;
factors = (Factor *)malloc(THREAD_COUNT*sizeof(Factor));

pthread_t ids[THREAD_COUNT];
pthread_attr_t attr[THREAD_COUNT];


sem_init(&factsum, 0, 1);

for(int i=0;i<THREAD_COUNT;i++)
{
		pthread_attr_init(&attr[i]);
}
i=0;

printf("Please Enter 5 integer Numbers: \n");

for (i=0; i<THREAD_COUNT; i++)
{
    printf("Please Enter Number %d:", i+1);
    scanf("%d", &factors[i].number);
    factors[i].index=i;
    pthread_create(&ids[i], &attr[i], factorial, &factors[i]);
}

i=0;

for (i = 0; i < THREAD_COUNT; i++)
{
		pthread_join(ids[i], 0);
}

i=0;

for (i=0; i<THREAD_COUNT; i++)
{
    printf("Total sum is: %d\n", moving_sum[i]);
}

sem_destroy(&factsum);

return 0;
}
