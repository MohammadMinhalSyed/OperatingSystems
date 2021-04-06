#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int listsize=10;
typedef struct proc
{
    char name[256];
    int priority;
    int pid;
    int runtime;
} proc;

typedef struct queue
{
    proc process;
    struct queue *next;
} queue;

struct proc push(struct proc pros)
{
    struct proc temp;
    temp = pros;
    return temp;
}


int main()
{
    int i=0;
    struct proc *processread;
    struct queue *linkedlist;

    processread = (proc*)malloc(listsize*sizeof(struct proc));
    linkedlist = (queue*)malloc(listsize*sizeof(struct queue));

    FILE *f1 = fopen("processes.txt" , "r");

    for ( i=0 ; i < listsize ; i++ )
	{
        fscanf(f1, "%10[^,]%*c%*c%d%*c%*c%d%*c%*c%d\n", processread[i].name, &processread[i].priority, &processread[i].pid, &processread[i].runtime);
        linkedlist[i].process= push(processread[i]);
        linkedlist[i+1].next=&linkedlist[i];

	}
	fclose(f1);

    for ( i=0 ; i < listsize ; i++ )
	{
        printf("List is: %d\n", i+1);
        printf("===================================\n");
        printf("Process name is: %s\n", linkedlist[i].process.name);
        printf("Process priority is: %d\n", linkedlist[i].process.priority);
        printf("Process pid is: %d\n", linkedlist[i].process.pid);
        printf("Process runtime is: %d\n", linkedlist[i].process.runtime);
        printf("===================================\n");

	}
    return 0;
}
