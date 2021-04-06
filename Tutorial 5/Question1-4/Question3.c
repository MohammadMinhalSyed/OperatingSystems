#define _XOPEN_SOURCE 600 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

typedef struct STUDENT{
                char student_name[256];
                int student_id;
                int mark;
} STUDENT;
int num_students=5;
int indexnum=0;
pthread_mutex_t lock;

void bellcurve(struct STUDENT *students)
{   
    pthread_mutex_lock(&lock);
    printf("--------------------------------------------\n");
    printf("Student name = %s\n", students->student_name);
    printf("Student ID = %d\n", students->student_id);
    printf("Curved mark is: %lf\n",1.5*students->mark);
    printf("--------------------------------------------\n");
    pthread_mutex_unlock(&lock);
    pthread_exit(0);
}



int main()
{
    
    struct STUDENT *students;
    students = (STUDENT *)malloc(num_students*sizeof(STUDENT));
    

    for(indexnum=0; indexnum<num_students; indexnum++){
        /*students[indexnum].student_name = (char*)calloc(256, sizeof(char));*/
        printf("Please Enter Below Info for Student # %d: \n", indexnum+1);
        printf("--------------------------------------------\n");
        printf("Please Enter Student Name: ");
        scanf("%s", &students[indexnum].student_name);
        printf("Please Enter Student ID: ");
        scanf("%d", &students[indexnum].student_id);
        printf("Please Enter mark: ");
        scanf("%d", &students[indexnum].mark);
        printf("--------------------------------------------\n");
        printf("\n");
    }

    pthread_t tid[5]; 
    pthread_attr_t attr[5]; 
    for(int i=0;i<5;i++){
        pthread_attr_init(&attr[i]);
    }
    for (int i=0; i<5; i++){
        
        pthread_create(&tid[i], &attr[i], bellcurve, &students[i]);
        
    }
    for (int i=0; i<5; i++){
        
        
        pthread_join(tid[i], 0);
    }
        
    pthread_mutex_destroy(&lock);
    free (students);
    return(0);
}
