#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<limits.h>
#include<string.h>
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
char arg_buffer[100][100];
int parse_command(char *command)
{
	int count=0
	char * token = strtok(command, " ");
    while( token != NULL )
    {
        strcpy(arg_buffer[i],token);
        token = strtok(NULL, " ");
        count++;
    }
	return count;
}

/*void shell_init()
{
	char *command;
	char **args;
	int status;
	while(true)
	{
		command = read_command();
		args = parse_command(command);
		status = exec_command(args);
	}
}*/
int main()
{
	char *x;
	x = read_command();
	int count = parse_command(x);
	for(int i=0;i<5;i++)
	{
		printf("cmd : %s\n",arg_buffer[i]);
	}
}