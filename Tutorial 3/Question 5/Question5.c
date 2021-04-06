#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct grade{
int student_id;
int mark;
} grade;


int num_students, indexnum=0;
char *professor;


int main(void){
    struct grade *grades;
    professor = (char*)calloc(256, sizeof(char));
    printf("Hello!\nPlease Enter Your Name: ");
	scanf("%[^\n]%*c", professor);
    printf("Enter Number of Students: ");
	scanf("%d", &num_students);

    grades = (grade *)malloc(num_students*sizeof(grade));

    printf("--------------------------------------------\n");
    for(indexnum=0; indexnum<num_students; indexnum++){
        printf("Please Enter Below Info for Student # %d: \n", indexnum+1);
        printf("--------------------------------------------\n");
        printf("Please Enter Student ID: ");
        scanf("%d", &grades[indexnum].student_id);
        printf("Enter mark for student ID %d: ", grades[indexnum].student_id);
        scanf("%d", &grades[indexnum].mark);
        printf("--------------------------------------------\n");
        printf("\n");
    }
    grade_students(grades, num_students);
    free(grades);
    free(professor);
    return 0;
}

void grade_students(struct grade *grades, int num_students){
    int index=0;
    double sum=0, mean=0, tempsum =0, std_dev=0;
    FILE *f = fopen("grades.txt" , "w");
    for (index=0;index<num_students; index++){
        sum += grades[index].mark;
        fprintf(f, "Student ID = %d, Mark = %d\n", grades[index].student_id, grades[index].mark);
    }
    mean = sum / ((double)num_students);
    index=0;
    for(index=0; index<num_students; index++){
        tempsum += pow(grades[index].mark - mean, 2);
    }
    std_dev = sqrt(tempsum/((double)num_students));
    fprintf(f, "Average = %lf\nStandard Deviation = %lf\n", mean, std_dev);
    fclose(f);
}
