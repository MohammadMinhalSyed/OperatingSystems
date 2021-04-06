#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
main()
{

    FILE* myFile;
    myFile = fopen("question2.txt", "r");

    //read file into array
    int numberArray[10];
    int i;

    for (i = 0; i < 10; i++)
    {
        fscanf(myFile, "%d", &numberArray[i]);
    }

    for (i = 0; i < 10; i++)
    {
        printf("Number is: %d\n\n", numberArray[i]);
    }
}

