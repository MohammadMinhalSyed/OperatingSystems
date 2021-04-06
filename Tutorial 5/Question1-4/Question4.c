#define _XOPEN_SOURCE 600 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include <unistd.h>

typedef struct grade{
                int mark;
} grade;
int num_students=10;
int indexnum=0;
int total_grade;
pthread_mutex_t lock;

void class_total(int mark)
{
    pthread_mutex_lock(&lock);
    total_grade += mark;
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
     
    for(int i=0;i<num_students;i++){
        pthread_attr_init(&attr[i]);
    }
    for (int i=0; i<num_students; i++){
        
        pthread_create(&tid[i], &attr[i], class_total, marks[i].mark);

        
    }
    for (int i=0; i<num_students; i++){
        
        

        pthread_join(tid[i], 0);   
    }
    printf("***********************************\n\n"); 
    printf("Total sum of the class is: %d \n\n", total_grade);
    printf("***********************************\n"); 
    pthread_mutex_destroy(&lock);
    free (marks);
    return(0);
}
