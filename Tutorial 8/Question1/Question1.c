#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int listsize=7;
typedef struct proc
{
    char parent[256];
    char name[256];
    int priority;
    int memory;
} proc;

typedef struct proc_tree
{
    struct proc data;
    struct proc_tree* left;
    struct proc_tree* right;
} proc_tree;

void insert(proc_tree * tree, proc data);
void print_tree(proc_tree * current);
void printDFS(proc_tree * current);

static const struct proc_tree *EmptyStruct;


void insert(proc_tree * tree, proc data)
{

  if (tree->data.priority == 0)
  {

    tree->data = data;
  }
  else
  {
    if (data.priority < tree->data.priority)
    {

      if (tree->left != NULL)
      {
        insert(tree->left, data);
      }
      else
      {
        tree->left = (proc_tree *) malloc(sizeof(proc_tree));
        tree->left->data = data;
        tree->left->left = NULL;
        tree->left->right = NULL;
      }
    }
    else
    {
      if (data.priority >= tree->data.priority)
      {

        if (tree->right != NULL)
        {
          insert(tree->right,data);
        }
        else
        {
          tree->right = (proc_tree *) malloc(sizeof(proc_tree));
          tree->right->data = data;
          tree->right->left = NULL;
          tree->right->right = NULL;
        }
      }
    }
  }
}




void printDFS(struct proc_tree *current)
{

  if (current == NULL)         return;
  if (current->left != NULL)   printDFS(current->left);
  if (current != NULL)
  {
        printf("Parent name is: %s\n", current->data.parent);
        printf("Name is: %s\n", current->data.name);
        printf("Priority is: %d\n", current->data.priority);
        printf("Memory is: %d\n", current->data.memory);
  }
  if (current->right != NULL)  printDFS(current->right);
}


int main()
{

  int i=0;
  struct proc *processread;
  processread = (proc*)malloc(listsize*sizeof(struct proc));
  proc_tree * test_list = (proc_tree *) malloc(sizeof(proc_tree));
  test_list = (proc_tree *) malloc(sizeof(proc_tree));

  test_list = &EmptyStruct;


  FILE *f1 = fopen("processes_tree.txt" , "r");

    for ( i=0 ; i < listsize ; i++ )
	{
        fscanf(f1, "%10[^,]%*c%*c%10[^,]%*c%*c%d%*c%*c%d\n", processread[i].parent, processread[i].name, &processread[i].priority, &processread[i].memory);
        insert(test_list, processread[i]);
	}
	fclose(f1);

  printDFS(test_list);
  printf("\n");
}


