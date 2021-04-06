#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
int main()
{
    char firstname[20];
    int age;
    char height[20];
    printf("Input your firstname: ");
    scanf("%s", firstname);
    printf("Input your age: ");
    scanf("%d", &age);
    printf("Input your height: ");
    scanf("%s", height);
    printf("%s %d %s\n", firstname, age, height);
    return 0;
}