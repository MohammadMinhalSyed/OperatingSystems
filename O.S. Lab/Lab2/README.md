# Operating Systems Lab 2

## Developing a Shell

### Commands

* cd ____________ - This changes the current default directory to the directory that is referred to after 'cd'. If the (directory) argument is not present, the current directory will be reported. If the directory does not not exist an error will be reported.
* clr - This will clear the screen.
* dir ____________ - This will list the contents of directory that is referref to after 'dir'(directory)
* environ - This will list all the environment strings.
* echo ____________ - This will display the comment that is given after 'echo' on the display followed by a new line
* help - This displays the user manual using the *more* filter
* pause - This will pause the operation of the shell until 'Enter' is pressed.
* quit - This will quit the shell.

### Concepts

**I/O Redirection**
* Three default files will always remain open, stdin, stdout and stderr. All files that are open (including the three default files), can be redirected meaning that the output from the file will be captured and sent to another file as input.
* This shell supports i/o redirection on both stdin and stdout
* command line *programname arg1 arg2 (inputfile) outputfile* will execute the program (programname) with both arguments (arg1 & arg2), the stdin file stream replaced by *inputfile* and the stdout file stream replaced by *outputfile*
* stdout redirection should also be possible for the internal commands *dir,environ, echo & help*

**Program Environment**
* Program maintains an environment that includes a set of variables defined by the login program, and the system and user initialization files. Some variables are defined by default.
* *Environment Variables* - are exported to all processes spawned by the shell.
* *Shell Variables* - affect only the current shell. These variables have a special relationship to a corresponding set of environment variables.
* To set shell variables, you use the lowercase names with the *set* command
* To set environment variables, you use the uppercase names with the *setenv* command.

**Background Program Environment**
* Running a program and not waiting for its completion, in order to complete other tasks refers to executing that program in the background.
* You can run a program in the background by specifying that it be a background process when you submit it or telling the shell to make it a background job after it has begun execution.
* To specifiy a job is to be executed in the background, you have to append an ampersand '&' to the end of the command.
