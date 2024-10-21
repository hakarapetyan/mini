#include "./include/minishell.h"

void my_pwd()
{
	char *cmd;

	cmd = getcwd(NULL, 0);
	if(cmd != NULL)
	{
		printf("%s\n", cmd);
		free(cmd);
	}
	else
		printf("error with memory allocation\n");
}

void my_echo_helper_one(int count, char **input, int i)
{
	int flag;

	flag = 0;
	while (i < count)
	{
		if (input[i] && ham_strcmp(input[i], "-n") == 0)
			i++;
		else
		{
			printf("%s",input[i]);
			i++;
		}
	}
}




void	my_echo_helper_two(int count, char **input, int i)
{
	int	j;

	j = 2;
	if(input[i] && input[i][0] == '-' && input[i][1] == 'n' && input[i][j] == 'n')
	{
		while(input[i] && input[i][0] == '-' && input[i][1] == 'n' && input[i][j] == 'n')
		{
			j++;
			i++;
		}
		while (i < count && input[i])
		{
			// if (input[i] && ham_strcmp(input[i], " ") == 0)
            //             	i++;
			if (input[i])
			{
				printf("%s ",input[i]);
				i++;
			}
		}
	}
	else
	{
		while (i < count && input[i])
		{
			printf("%s ",input[i]);
			i++;
		}
		printf("\n");
	}
}


void my_echo(int count, char **args)
{
	int	i;

	i = 0;
	while (args[i] && (!ft_strcmp(args[i], "echo")))
		i++;
	if (args[i] && !ham_strcmp(args[i], "-n"))
	{
		i++;
		my_echo_helper_one(count, args, i);
	}
	else
	{
		if (args[i] && !ham_strcmp(args[i], "-n") && !args[i + 1])
			return ;
		my_echo_helper_two(count, args, i);
	}
}

int	ham_strlen(char *str)
{
	int	i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}


int	ham_strcmp(char *s1, char *s2)
{
	int	i;
	i = 0;
	while ((s1[i] == s2[i]) && (s1[i] && s2[i]))
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

void	execute_echo(t_shell *shell)
{
	t_commands *cmd;

	cmd = shell -> command;
	while (cmd)
	{
		if (cmd && ham_strcmp(cmd -> name, "echo") == 0)
		{
			printf("name=%s\n", cmd->name);
			my_echo(shell -> token_count, cmd -> args);
		}
		cmd = cmd -> next;
	}
}
