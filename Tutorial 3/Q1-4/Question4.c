#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h> 
#include <stdio.h> 

int main(void) { 
	//creating Pointers
	typedef struct {
		int student_id;
		int grades;
	} STUDENT;

	typedef struct{
		int s_id;
		int mark;
	} GRADE;

	typedef struct{
		char* Professor;
	} PROFESSOR;

	int n;

	//Allocatiing 256 chars to professor and prompting the prof for 
	//required information
	PROFESSOR* Professor;
	Professor = (char*)calloc(256, sizeof(char));
	printf("Hello!\nPlease Enter Your Name: ");
	scanf("%[^\n]%*c", Professor);
	printf("Enter Number of Students: ");
	scanf("%d", &n);

	//Allocating Memory for grades and Student_id's using Malloc
	GRADE* grades;
	grades = (GRADE*)malloc(n * sizeof(GRADE));
	
	STUDENT* student_id;
	student_id = (STUDENT*)malloc(n * sizeof(n));

	//Free memory
	free(Professor);
	free(student_id);
	free(grades);
	return 0;
} 




