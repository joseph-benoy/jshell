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
	if(strlen(command_buffer)>0)
	{
		add_history(command_buffer);
	}
	return command_buffer;
}

//parsing the command
char **parse_command(char *line)
{
	int postion=0,buffer_size=64;	
	char **arg_buff = malloc(buffer_size*sizeof(char*));
	if(!arg_buff)
	{
		perror("JShell Error");
	}
	char * token = strtok(line, " \t\n\r\a");
	while(token != NULL) 
	{
		arg_buff[postion] = token;
		postion++;
		token = strtok(NULL, " \t\n\r\a");
		if(postion>=64)
		{
			realloc(arg_buff,buffer_size*sizeof(char*));
			if(!arg_buff)
			{
				perror("JShell error");
			}
		}
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
			perror("JShell Error");
		}
	}
	else if(pid<0)
	{
		perror("JShell error");
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
	printf("\e[1;1H\e[2J");
	shell_init();
}