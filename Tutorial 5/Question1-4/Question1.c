#define _XOPEN_SOURCE 600 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *hello_world()
{
    printf("hello world!\n");
    srand(time(NULL));   
    int r = rand() % 5; 
    sleep(r);
    pthread_exit(0);
}

void *goodbye()
{
    printf("goodbye\n");
    srand(time(NULL));   
    int r = rand() % 5; 
    sleep(r);
    pthread_exit(0);
}

int main()
{
    
    pthread_t tid[2]; 
    pthread_attr_t attr[2]; 
    for(int i=0;i<2;i++){
        pthread_attr_init(&attr[i]);
    }
    for (int i=0; i<2; i++){
        if (i==0){
            pthread_create(&tid[i], &attr[i], hello_world, NULL);
        }
        if (i==1){
            pthread_create(&tid[i], &attr[i], goodbye, NULL);
        }
    }
     
        
    for(int i=0;i<2;i++){
        pthread_join(tid[i], 0);    
    }
    return(0);
}
