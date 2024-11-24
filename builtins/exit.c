/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakarape <hakarape@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:24:31 by hakarape          #+#    #+#             */
/*   Updated: 2024/11/24 16:10:47 by hakarape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int is_digit(char *arg)
{
    int i;
    
    i = 0;
    if (arg[i] == '+' || arg[i] == '-')
		i++;
    while (arg[i])
    {
        if (arg[i] >= 48 && arg[i] <= 57)
            i++;
        else
        {
        	printf("exit\nminishell: exit: %s: numeric argument required", arg);
        	return (1);
        }
    }
    return (0);
}
// int	check_int(char *arg)
// {
// 	if (ft_strcmp(*arg, INT_MAX_8) > 0 || ft_strcmp(*arg, INT_MIN_8) < 0)
// 	{
// 		printf("exit\nminishell: exit: %s: numeric argument required", arg);
// 		return (1);
// 	}
// 	return (0);
// }
static int	norm_my_exit(int args,char **argv, int i)
{
	if (args == 1)
	{
		printf("exit\n");
		return (0);
	}
	else if (args == 2)
	{
		if (is_digit(argv[i])/*|| check_int(argv[i])*/)
			return (1);
		else
		{
			printf("exit\n");
			return (0);
		}
	}
	else
	{
		if (is_digit(argv[i]))
			return (1);
		return (2);
	}
	
}
int my_exit(int args, char **argv, t_shell *shell)
{
	int	i;
	int	exit;

	i = 0;
	if (argv[i] && ft_strcmp(argv[i], "exit") == 0)
		i++;
	exit = norm_my_exit(args, argv, i);
	if (exit == 1)
		return (1);
	else if (exit == 2)
		return (2);
	else
		return (0);
}
int execute_exit(t_shell *shell)
{
	t_commands *cmd;
	int	func;

	cmd = shell -> command;

	func = my_exit(shell -> token_count, cmd -> args, shell);
	if(func == 1)
		exit(1);
	else if (func == 2)
		printf("exit\nminshell: exit: too many arguments\n");
	else
		exit(0);	
}

