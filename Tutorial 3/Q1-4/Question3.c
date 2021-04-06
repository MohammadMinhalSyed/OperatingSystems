#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h> 
#include <stdio.h> 

struct STUDENT {
	int id;
	int age;
	int year;
}s;

void save_student(struct STUDENT* s) {
    //Append to the students.txt file
    FILE* outf = fopen("students.txt", "a");
    //Print the ID, Age & Year from struct and add to file 
    fprintf(outf, "ID: %d ", s->id);
    fprintf(outf, "Age: %d ", s->age);
    fprintf(outf, "Year: %d\n", s->year);
    // close the file
    fclose(outf);
}

int main() {
    //Storing values entered by user into the student struct
    struct STUDENT s;
    //store the ID, Age and Year
	printf("Student ID: ");
	scanf("%d", &s.id);
    printf("Age: ");
    scanf("%d", &s.age);
    printf("Year Started: ");
    scanf("%d", &s.year);
    //Calling the save_student function to save data to the Students.txt file
    save_student(&s);
  	return 0;
}