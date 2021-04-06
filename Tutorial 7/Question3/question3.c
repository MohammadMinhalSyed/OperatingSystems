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

void sighup(int); /* routines child will call upon sigtrap */
void sigint(int);
void sigquit(int);

  int main(void)
  {
  	struct sigaction sigact;
    sigact.sa_flags = 0;
    sigemptyset(&sigact.sa_mask);

    sigact.sa_handler = sighup;
    if (sigaction(SIGHUP, &sigact, NULL) < 0) {
        perror("sigaction()");
        exit(1);
    }

    sigact.sa_handler = sigint;
    if (sigaction(SIGINT, &sigact, NULL) < 0) {
        perror("sigaction()");
        exit(1);
    }

    sigact.sa_handler = sigquit;
    if (sigaction(SIGQUIT, &sigact, NULL) < 0) {
        perror("sigaction()");
        exit(1);
    }


    pid_t pid = fork();
    if (pid < 0) {
    	perror("fork failed");
    	exit(1);
    }

    if (pid == 0) {
    	char* args[] = {"./process"};
    	execv(args[0], args);
    	for (;;);
    } else {
    	sigact.sa_handler = SIG_DFL;
        sigaction(SIGHUP, &sigact, NULL);
        sigaction(SIGINT, &sigact, NULL);
        sigaction(SIGQUIT, &sigact, NULL);

        /* parent */
        /* pid hold id of child */
        kill(pid,SIGHUP);
        sleep(5); /* pause for 5 secs */
        kill(pid,SIGINT);
        sleep(5); /* pause for 5 secs */
        kill(pid,SIGQUIT);
        sleep(5);
    }

    return 0;
}

void sighup(int signo) {
    signal(SIGHUP,sighup); /* reset signal */

}

void sigint(int signo) {
    signal(SIGINT,sigint); /* reset signal */

}

void sigquit(int signo) {
    exit(0);
}

