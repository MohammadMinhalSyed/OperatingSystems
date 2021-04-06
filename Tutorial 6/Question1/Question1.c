#define _XOPEN_SOURCE 700 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
char c1[256];
char c2[256];
int main()
{
pid_t pid1, pid2;
FILE *f1 = fopen("child1.txt" , "w");
fprintf(f1, "child 1\n");
fclose(f1);
FILE *f2 = fopen("child2.txt" , "w");
fprintf(f2, "child 2\n");
fclose(f2);

pid1 = fork(); /* assume fork not failed, if failed then pid1=-1*/
if (pid1 == 0)
{ /* child process */
    sleep(1);
    FILE *f3 = fopen("child1.txt", "r");
    fscanf(f3, "%[^\n]", c1);
    printf("%s\n", c1);
    fclose(f3);
}
else
{
wait(NULL);
pid2 = fork();
if (pid2 == 0)
{ /* child process */
    sleep(1);
    FILE *f4 = fopen("child2.txt", "r");
    fscanf(f4, "%[^\n]", c2);
    printf("%s\n", c2);
    fclose(f4);
}
wait(NULL);
}

return 0;
}
