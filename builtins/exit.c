/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:33:04 by hakarape          #+#    #+#             */
/*   Updated: 2024/12/11 14:35:43 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"


// static int	check_int(char *arg)
// {
// 	printf("arg=%c\n", *arg);
// 	printf("argum=%s\n", arg);
// 	if (ft_strcmp(arg, INT_MAX_8) > 0 || (ft_strcmp(arg, INT_MIN_8) > 0 && *arg == '-'))
// 	{
// 		printf("good\n");
// 		//printf("exit\nminishell: exit: %s: numeric argument required\n", arg);
// 		write(STDERR_FILENO, "exit\n", 5);
// 		simple_error(255, arg, "numeric argument required");
// 		return (1);
// 	}
// 	return (0);
// }
static int	ft_nbr(const char *str)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	while ((str[i] >= '0' && str[i] <= '9') && str[i])
	{
		n = n * 10 + (str[i] - '0');
		i++;
	}
	return (n);
}
long	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	count;

	sign = 1;
	i = 0;
	count = 0;
	while (((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			sign = -1;
			count++;
		}
		else if (str[i] == '+')
			count++;
		i++;
	}
	if (count > 1)
		return (0);
	return (ft_nbr(&str[i]) * sign);
}
static int exit_status(char *argv)
{
	long num;
	int tmp;
	if (!argv)
		return (0);
	num = ft_atoi(argv);
	if (num >= 0)
		return (num % 256);
	else if (num < 0)
	{
	    tmp = num % 256;
	   if (tmp)
	    tmp = tmp + 256;
	   else
	    return (tmp);
	return (tmp);
	}
	return (0);
}
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
			// write(STDERR_FILENO, "exit\n", 5);
			// simple_error(255, arg, "numeric argument required");
        	//printf("exit\nminishell: exit: %s: numeric argument required\n", arg);
        	return (1);
        }
    }
    return (0);
}
static int	norm_my_exit(int args,char **argv, int i)
{
	int	status;

	status = exit_status(argv[i]);
	if (args == 1)
	{
		printf("exit\n");
		return (set_status(SUCCESS), 0);
	}
	else if (args == 2)
	{
		if(is_digit(argv[i]))
			return(1);
		else
		{
			printf("exit\n");
			set_status(status);
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
int my_exit(int args, char **argv)
{
	int	i;
	int	exit;

	i = 0;
	if (argv[i] && ft_strcmp(argv[i], "exit") == 0)
		i++;
	exit = norm_my_exit(args, argv, i);
	if (exit == 1)
	{
		write(STDERR_FILENO, "exit\n", 5);
		simple_error(255, "exit", "numeric argument required");
		return (1);
	}
	else if (exit == 2)
		return (2);
	else
		return (0);
}
void execute_exit(t_shell *shell, t_commands *command)
{
	// t_commands *cmd;
	int	func;

	//cmd = shell -> command;

	func = my_exit(shell -> token_count, command -> args);
	if(func == 1)
	{
		free_env(shell->env);
		free_env(shell->exp);
		free_shell(shell);
		//printf("gnac\n");
		exit(get_status());
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
		exit(get_status());
	}
}

