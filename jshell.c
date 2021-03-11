#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<limits.h>
#include<string.h>
#include<sys/wait.h>
#include<readline/readline.h>
#include<readline/history.h>

//prompt construction function
void get_prompt()
{
	char user[50];
	char cwd[PATH_MAX];
	getcwd(cwd,PATH_MAX);
	getlogin_r(user,50);
	char hostname[HOST_NAME_MAX];
	gethostname(hostname,HOST_NAME_MAX);
	strcat(user,"@");
	strcat(user,hostname);
	strcat(user,":");
	strcat(user,cwd);
	printf("%s",user);
}
//reading the command
char* read_command()
{
	char *command_buffer;
	get_prompt();
	command_buffer = readline("> ");
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
			arg_buff = realloc(arg_buff,buffer_size*sizeof(char*));
			if(!arg_buff)
			{
				perror("JShell error");
			}
		}
	}
    arg_buff[postion] = NULL;
    return arg_buff;
}

//JShell cd command
int jshell_cd(char **arg_buff)
{
	chdir(arg_buff[1]);
}

//JShell exit command
int jshell_exit()
{
	printf("Stopping jobs......\nExiting.....\n");
	exit(0);
}

int jshell_help()
{
	printf("help\n");
}

int command_identifier(char *command)
{
	if(strcmp(command,"cd")==0)
	{
		return 1;
	}
	else if(strcmp(command,"exit")==0)
	{
		return 2;
	}
	else if(strcmp(command,"help")==0)
	{
		return 3;
	}
	return 0;
}
//execute command
int exec_command(char **arg_buffer)
{
	int command_type = command_identifier(arg_buffer[0]);
	if(command_type==1)
	{
		jshell_cd(arg_buffer);
	}
	else if(command_type==2)
	{
		jshell_exit();
	}
	else if(command_type==3)
	{
		jshell_help();
	}
	else
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