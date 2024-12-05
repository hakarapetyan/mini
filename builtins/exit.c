/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakarape <hakarape@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:33:04 by hakarape          #+#    #+#             */
/*   Updated: 2024/12/05 19:13:07 by hakarape         ###   ########.fr       */
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
			write(STDERR_FILENO, "exit\n", 5);
			simple_error(255, arg, "numeric argument required");
        	//printf("exit\nminishell: exit: %s: numeric argument required\n", arg);
        	return (1);
        }
    }
    return (0);
}

static int	check_int(char *arg)
{
	printf("arg=%c\n", *arg);
	printf("argum=%s\n", arg);
	if (ft_strcmp(arg, INT_MAX_8) > 0 || (ft_strcmp(arg, INT_MIN_8) > 0 && *arg == '-'))
	{
		printf("good\n");
		//printf("exit\nminishell: exit: %s: numeric argument required\n", arg);
		write(STDERR_FILENO, "exit\n", 5);
		simple_error(255, arg, "numeric argument required");
		return (1);
	}
	return (0);
}
static int	norm_my_exit(int args,char **argv, int i)
{
	if (args == 1)
	{
		printf("exit\n");
		return (0);
	}
	else if (args == 2)
	{
		// if (check_int(argv[i]))
		// 	return (1);
		if(is_digit(argv[i]))
			return(1);
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
void execute_exit(t_shell *shell)
{
	t_commands *cmd;
	int	func;

	cmd = shell -> command;

	func = my_exit(shell -> token_count, cmd -> args, shell);
	if(func == 1)
	{
		free_env(shell->env);
		free_env(shell->exp);
		free_shell(shell);
		exit(1);
	}
	else if (func == 2)
		{
			write(STDERR_FILENO, "exit\n", 5);
			simple_error(EXIT_FAILURE, "exit", "too many arguments");
		}
	else
	{
		free_env(shell->env);
		free_env(shell->exp);
		free_shell(shell);
		exit(0);
	}
}

