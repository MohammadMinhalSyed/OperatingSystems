#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stddef.h> 
#include <stdlib.h> 
#include <stdbool.h> 
#include <signal.h> 
#include <sys/wait.h> 
#include <errno.h>

int main(void)
{
    int stop;
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        execv("process", NULL);
    } else {
        sleep(5); /* pause for 5 secs */
        kill(pid, SIGTSTP);
        sleep(10);
        kill(pid, SIGCONT);
        waitpid(pid, &stop, 0);
        return stop;
    }
}