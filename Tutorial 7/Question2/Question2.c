#include <string.h>
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

struct queue *linkedlist;
static const struct queue EmptyStruct;

struct proc pop(){
    int ii=0;
    struct proc temp;
    temp=linkedlist[0].process;
    for (ii=0;ii<listsize-1;ii++){
        linkedlist[ii]=linkedlist[ii+1];

    }
    linkedlist[listsize]=EmptyStruct;

    return temp;
}

struct proc delete_name(char *name)
{
    int i=0;
    int result;
    int checker=0;
    struct proc temp;

    for (i=0;i<listsize;i++)
    {
        result = strcmp(linkedlist[i].process.name, name);
        if (result==0)
        {
            checker=1;
            temp=linkedlist[i].process;
            linkedlist[i]=EmptyStruct;
            for (int j=i; j<listsize-1;j++){
                linkedlist[j]=linkedlist[j+1];
            }
            linkedlist[listsize-1]=EmptyStruct;
            return temp;
        }
    }
    if (checker==0)
    {
        return EmptyStruct.process;
    }
}

struct proc delete_pid(int pid)
{
    int i=0;
    int checker=0;
    struct proc temp;

    for (i=0;i<listsize;i++)
    {
        if (linkedlist[i].process.pid==pid)
        {
            checker=1;
            temp=linkedlist[i].process;
            linkedlist[i]=EmptyStruct;
            for (int j=i; j<listsize-1;j++)
            {
                linkedlist[j]=linkedlist[j+1];
            }
            linkedlist[listsize-1]=EmptyStruct;
            return temp;
        }
    }

    if (checker==0)
    {
        return EmptyStruct.process;
    }
}



struct proc push(struct proc pros)
{
    struct proc temp;
    temp = pros;
    return temp;
}




int main()
{
    int i=0;
    char *nn;
    struct proc *processread;
    struct proc processinuse;

    processread = (proc*)malloc(listsize*sizeof(struct proc));
    //processinuse = (proc*)malloc(sizeof(struct proc));
    linkedlist = (queue*)malloc(listsize*sizeof(struct queue));

    FILE *f1 = fopen("processes.txt" , "r");

    for ( i=0 ; i < listsize ; i++ )
	{
        fscanf(f1, "%10[^,]%*c%*c%d%*c%*c%d%*c%*c%d\n", processread[i].name, &processread[i].priority, &processread[i].pid, &processread[i].runtime);
        linkedlist[i].process= push(processread[i]);
        linkedlist[i+1].next=&linkedlist[i];

	}
	fclose(f1);

	processinuse=delete_name("emacs");
    processinuse=delete_pid(12235);
    int j=1;

    while ( (linkedlist[0].process.name != NULL) && (linkedlist[0].process.name[0] != '\0'))
    {
            processinuse=pop();
            printf("List is: %d\n", j);
            printf("===================================\n");
            printf("Process name is: %s\n", processinuse.name);
            printf("Process priority is: %d\n", processinuse.priority);
            printf("Process pid is: %d\n", processinuse.pid);
            printf("Process runtime is: %d\n", processinuse.runtime);
            printf("===================================\n");
            j++;
	}

    return 0;
}
