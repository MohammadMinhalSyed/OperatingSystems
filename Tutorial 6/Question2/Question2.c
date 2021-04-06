#define _XOPEN_SOURCE 700 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
pid_t pid;
int status;
pid = fork(); /* assume fork not failed, if failed then pid1=-1*/
if (pid == 0)
{ /* child process */
    sleep(1);
    printf("Child process\n");
}
else
{
wait(&status);
sleep(1);
printf("Child status is: %d \n", status);
sleep(1);
printf("Parent process\n");
}

return 0;
}
