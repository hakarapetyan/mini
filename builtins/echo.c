/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 14:12:18 by hakarape          #+#    #+#             */
/*   Updated: 2024/12/14 16:16:37 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void my_echo_helper_one(int count, char **input, int i)
{
	while (i < count)
	{
		if (input[i] && ham_strcmp(input[i], "-n") == 0)
			i++;
		else
		{
			if (i == count - 1)
				printf("%s",input[i]);
			else
				printf("%s ",input[i]);
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
				if (i == count - 1)
					printf("%s",input[i]);
				else
					printf("%s",input[i]);
				i++;
		}
	}
	else
	{
		while (i < count && input[i])
		{
			if (i == count - 1)
				printf("%s",input[i]);
			else
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
// void	execute_echo(t_shell *shell)
// {
// 	t_commands *cmd;

// 	cmd = shell -> command;
// 		if (cmd && ham_strcmp(cmd -> name, "echo") == 0)
// 			my_echo(shell -> token_count, cmd -> args);
// }

