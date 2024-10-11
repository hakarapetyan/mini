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

void my_echo_helper_one(int argc, char **argv, int i)
{
		while (i < argc)
		{
			while (ft_strcmp(argv[i], "-n") == 0)
				i++;
			printf("%s",argv[i]);
			if (i != argc -1)
				printf(" ");
			i++;
		}
}

void my_echo_helper_two(int argc, char **argv, int i)
{
	int	j;

	j = 2;
	//printf("argv1=%s\n", argv[1]);
	while (argv[1][0] == '-' && argv[1][1] == 'n' && argv[1][j] == 'n' && j < ham_strlen(argv[1]))
	{
		j++;
		i = 2;
	}
	while (i < argc)
	{
		printf("%s",argv[i]);
		if (i != argc -1)
			printf(" ");
		i++;
	}
	printf("\n");
	
}

void my_echo(int argc, char **argv)
{
	int	i;
//	printf("argv=%s\n", argv[0]);
	if (ft_strcmp(argv[1], "-n") == 0)
	{
		i = 2;
		my_echo_helper_one(argc, argv, i);
	}
	else
	{
		i = 1;
		my_echo_helper_two(argc, argv, i);
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
		if (ham_strcmp(cmd -> name, "echo ") == 0)
		{
			//cmd -> args[i++];
			//cmd -> args[0][i++];
			my_echo(shell -> token_count, cmd -> args);
		}
		cmd = cmd -> next;
	}
}