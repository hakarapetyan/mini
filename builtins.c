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
			while (input[i] && ham_strcmp(input[i], "-n") == 0)
				i++;
			// if (input[i] && (ham_strcmp(input[i], "-n") == 0 && input[i + 1] && ham_strcmp(input[i + 1], " ") == 0))
			// {
			// 		i++;
			// 	// while (ham_strcmp(input[i], "-n"))
			// 	// {
			// 	// 	printf("%s",input[i]);
			// 	// 	i++;
			// 	// }
			// }
					printf("%s",input[i]);
					i++;
			//printf("--[%s]\n",input[i]);
			// while (input[i] && input[i + 1] && ham_strcmp(input[i + 1], " ")&& (ham_strcmp(input[i], "-n") == 0 || ham_strcmp(input[i], " ") == 0))
			// i++;
			//if (ham_strcmp(input[i], "-n"))
			//i++;
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
		while (i < count)
		{
			printf("%s",input[i]);
			i++;
		}
	}
	else
	{
		while (i < count)
		{
			printf("%s",input[i]);
			i++;
		}
		printf("\n");
	}
}

// void my_echo(int argc, char **input)
// {
// 	int	i;
// 	//printf("input=%s\n", input[2]);
// 	if (argc > 2 && input[2] && ham_strcmp(input[2], "-n") == 0)
// 	{
// 		i = 3;
// 		my_echo_helper_one(argc, input, i);
// 	}
// 	else
// 	{
// 		i = 1;
// 		my_echo_helper_two(argc, input, i);
// 	}
// }

void my_echo(int count, char **args)
{
	int	i;

	i = 0;
	while (!ham_strcmp(args[i], " ") || !ham_strcmp(args[i], "echo"))
		i++;
	if (!ham_strcmp(args[i], "-n"))
	{
		i++;
		my_echo_helper_one(count, args, i);
	}
	else
	{
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
	while ((s1[i] == s2[i]) && s1[i] && s2[i] && !is_space(s1[i]) && !is_space(s2[i]))
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

void	execute_echo(t_shell *shell)
{
	t_commands *cmd;
	//int i = 0;

	cmd = shell -> command;
	while (cmd)
	{
		if (ham_strcmp(cmd -> name, "echo") == 0)
		{
			//cmd -> args[i++];
			//cmd -> args[0][i++];
			//printf("%s %s\n",cmd -> args[0],cmd -> args[1]);
			my_echo(shell -> token_count, cmd -> args);
		}
		cmd = cmd -> next;
	}
}
