#define _XOPEN_SOURCE 600 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include <unistd.h>

typedef struct grade{
                int mark;
} grade;
int num_students=5;
int indexnum=0;
pthread_mutex_t lock;

void bellcurve(int mark)
{   
    pthread_mutex_lock(&lock);
    printf("Curved mark is: %lf\n",1.5*mark);
    pthread_mutex_unlock(&lock);
    pthread_exit(0);
}



int main()
{
    struct grade *marks;
    marks = (grade *)malloc(num_students*sizeof(grade));

    for(indexnum=0; indexnum<num_students; indexnum++){
        printf("Please Enter grade of student # %d: \n", indexnum+1);
        scanf("%d", &marks[indexnum].mark);
        printf("--------------------------------------------\n");
    }

    pthread_t tid[num_students]; 
    pthread_attr_t attr[num_students]; 
    for(int i=0;i<5;i++){
        pthread_attr_init(&attr[i]);
    }
    for (int i=0; i<num_students; i++){
        
        pthread_create(&tid[i], &attr[i], bellcurve, marks[i].mark);

        
    }

    for (int i=0; i<num_students; i++){
        
        

        pthread_join(tid[i], 0);   
    } 
    pthread_mutex_destroy(&lock);
    free (marks);
    return(0);
}
