/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   another_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakarape <hakarape@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:48:42 by hakarape          #+#    #+#             */
/*   Updated: 2024/10/24 16:45:53 by hakarape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	my_cd_helper(char **argv, int i)//cd -
{
	char	*cmd;
	char	*tmp;
	
	cmd = getcwd(NULL, 0);
	tmp = cmd;

	if (argv[i] && argv[i] != '-')
	{
		if (cmd != NULL)
		{
			if (!chdir(argv[i]))
			{
				cmd = getcwd(NULL, 0);
				printf("cm=%s\n", cmd);
			}
			else /*if (argc != 2)*/
				printf("cd: %s: No such file or directory\n", argv[i]);
		}
		else
			printf("%s\n", "path not found");
	}
	else if (argv[i] && argv[i] == '-')
	{
		
	}
	else
		printf("get=%s", cmd);
}

void	my_cd(int argc, char **argv)
{
	int	i;
	char	*home;
	i = 0;

	if (argc > 1)
	{
	while (argv[i] && (!ft_strcmp(argv[i], "cd")))
		i++;
	//if (argv[i])
		my_cd_helper(argv, i);
	}
	else
	{
		home = getenv("HOME");
		chdir(home);
		printf("home%s", home);
	}
}

void	execute_cd(t_shell *shell)
{
	t_commands *cmd;

	cmd = shell -> command;

	if (ft_strcmp(cmd -> name, "cd") == 0)
		my_cd(shell -> token_count, cmd -> args);
}