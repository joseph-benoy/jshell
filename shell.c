#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<limits.h>
#include<readline/readline.h>
#include<readline/history.h>
//reading the command
char* read_command()
{
	char *command_buffer;
	command_buffer = readline("\n>");
	if(strlen(command_buffer)<0)
	{
		return 0;
	}
	return command_buffer;
}

//parsing the command
char** parse_command(char *command)
{


}

void shell_init()
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
}
int main()
{
	shell_init();
	return EXIT_SUCCESS;
}