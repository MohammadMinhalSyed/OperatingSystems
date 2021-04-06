#define _XOPEN_SOURCE 700 //required for barrierrs to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define Numbers 10 // Maximum items a producer can produce or a consumer can consume
#define BufferSize 5 // Size of the buffer

int holder[Numbers];

sem_t empty;
sem_t full;
int in = 0;
int out = 0;
int buffer[BufferSize];


void *producer(int *number)
{
    int r;
    sem_wait(&empty);

    for(int i = 0; i < Numbers; i++)
    {
            if (buffer[i] == 0)
            {

            buffer[i] = number[i];
            printf("Produced %d: \n", number[i]);
            r = rand() % 5;
            sleep(r);
            }
            else {i = i -1;}


    }
    sem_post(&empty);
}

void *consumer(void )
{
    int r ;
    sem_wait(&full);
    for(int i = 0; i < Numbers; i++)
    {
    if (buffer[i] != 0 ){

            printf("Consumer %d: \n", buffer[i]);
            buffer[i] = 0;
            r = rand() % 5;
            sleep(r);
    }
    else {i=i-1;}
    }
    sem_post(&full);
}

int main()
{
    int i=0;
    pthread_t pro,con;

    sem_init(&empty,0,1);
    sem_init(&full,0,1);
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    for (i=0 ; i < Numbers ; i++)
    {
        printf("Enter number %d\n", i+1);
        scanf("%d", &holder[i]);
    }

    pthread_create(&pro, &attr, (void *)producer, holder);
    pthread_create(&con, &attr, (void *)consumer, NULL);


    pthread_join(pro, NULL);
    pthread_join(con, NULL);

    printf("\nHere is the buffer content:\n");
    for(int i = 0; i < 5; i++) {
        printf("Buffer %d is: %d\n",i+1, buffer[i]);
    }

    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;

}
