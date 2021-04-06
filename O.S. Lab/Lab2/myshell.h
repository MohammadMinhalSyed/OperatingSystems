#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h> 
#include <ctype.h>


//max line buffer
#define MAX_BUFFER 1024
//max # args
#define MAX_ARGS 64
//token sparators
#define SEPARATORS " \t\n" 
//the command number
#define NUM 10        
//open 10 stdin redirection files max and 10 stdout redirection files, myshell support several I/O redirection£©
#define MAX_OPEN 10  
//the maxium length of file and forder 
#define MAX_PATH 100 


/***********************************************************************
Data-Types
***********************************************************************/
/*redirection date structure, redirection file name
the open method of redirection files "a"   "r"   "w" 
the open method of redirection files  ">>"   "<"   ">" 
*/
typedef struct
{ 
	char *filename;
	char opentype[3]; 
	char open[3];  
} Redirect;          

// system error number
extern int errno; 
// environment array
extern char **environ;   


/***********************************************************************
Functions
***********************************************************************/
//the execution of the command
int execute(char *buffer);
//
int Command_exec(char **args, const Redirect *Inputs,const Redirect *Outputs,int *states);
//error message printout
int Error(int errortype,char **args,const Redirect *  IOputs,const int *states, char * msg) ;
//analyse the command
int Command_strtok(char *buf,char **args,int *states,Redirect *InPuts,Redirect *OutPuts);
// execute command 'cd' 
int Command_cd(char **args,const Redirect *Inputs, int *states);
// execute command 'clear' 
void Command_clear(void);
// execute command 'dir'  
int Command_dir(char **args,const Redirect *Inputs, int *states);
//execute command 'pwd'
int show_pwd(void);