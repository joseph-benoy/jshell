#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<limits.h>
#include<string.h>
#include<sys/wait.h>
#include<readline/readline.h>
#include<readline/history.h>
//reading the command
char* read_command()
{
	char *command_buffer;
	command_buffer = readline(">");
	return command_buffer;
}
//parsing the command
char **parse_command(char *line)
{
	int postion=0,buffer_size=128;
	char **arg_buff = malloc(buffer_size*sizeof(char*));
	char * token = strtok(line, " \t\n\r\a");
    while( token != NULL ) {
    	arg_buff[postion] = token;
    	postion++;
        token = strtok(NULL, " \t\n\r\a");
   }
   arg_buff[postion] = NULL;
   return arg_buff;
}
//execute command
int exec_command(char **arg_buffer)
{
	int pid;
	pid = fork();
	if(pid==0)
	{
		if(execvp(arg_buffer[0],arg_buffer)==-1)
		{
			perror("Execution error : ");
		}
	}
	else if(pid<0)
	{
		perror("shell error : ");
	}
	else
	{
		wait(NULL);
	}
	return 1;
}
//shell initialization function
void shell_init()
{
	char *command;
	char **args;
	int status;
	while(1)
	{
		command = read_command();
		args = parse_command(command);
		status = exec_command(args);
	}
}
int main()
{
	shell_init();
}