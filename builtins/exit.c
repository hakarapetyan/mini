/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakarape <hakarape@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:24:31 by hakarape          #+#    #+#             */
/*   Updated: 2024/12/17 14:09:57 by hakarape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"


static unsigned	long ft_number(const char *str)
{
	int	i;
	unsigned long n;

	n = 0;
	i = 0;
	while ((str[i] >= '0' && str[i] <= '9') && str[i])
	{
		n = n * 10 + (str[i] - '0');
		i++;
	}
	return (n);
}
int max_min(char *str, int sign, int *flag)
{
	unsigned long n;

	n = ft_number(str);

	if (sign == -1)
	{
		if (n > MAX_MIN)
		{
			*flag = 1;
			return (1);
		}
	}
	else
		if (n > 9223372036854775807)
		{
			*flag = 1;
			return (1);
		}
	return (0);

}
unsigned long	l_atoi(char *str, int *flag)
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
	if (max_min(&str[i], sign, flag))
		return(1);
	if (count > 1)
		return (0);
	return (ft_number(&str[i]) * sign);
}

static int is_digit(char *arg)
{
    int i;
	int	flag;

    i = 0;
	flag = 0;
	if (ft_strlen(arg) > 20)
		return (1);
	if (l_atoi(arg, &flag) == 1 && flag)
		return (1);
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
static int	norm_my_exit(int pipe_count, int args,char **argv, int i)
{
	int	status;

	status = exit_status(argv[i]);
	if (args == 1)
	{
		if (pipe_count == 0)
			printf("exit\n");
		return (set_status(SUCCESS), 0);
	}
	else if (args == 2)
	{
		if(is_digit(argv[i]))
			return(1);
		else
		{
			if (pipe_count == 0)
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
int my_exit(int pipe_count, int args, char **argv)
{
	int	i;
	int	exit;

	i = 0;
	if (argv[i] && ft_strcmp(argv[i], "exit") == 0)
		i++;
	exit = norm_my_exit(pipe_count, args, argv, i);
	if (exit == 1)
	{
		if (pipe_count == 0)
			write(STDERR_FILENO, "exit\n", 5);
		//simple_error(255, "exit", "numeric argument required");
		another_simple_error(255, "exit: ", argv[1], "numeric argument required");
		return (1);
	}
	else if (exit == 2)
		return (2);
	else
		return (0);
}
void execute_exit(t_shell *shell, t_commands *cmd)
{
	//t_commands *cmd;
	int	func;

//	cmd = shell -> command;

	func = my_exit(shell -> pipe_count, cmd -> arg_count, cmd -> args);
	if(func == 1)
	{
		free_env(shell->env);
		shell -> env = NULL;
		free_env(shell->exp);
		shell -> exp = NULL;
		free_shell(shell);
		//system("leaks minishell");
		exit(get_status());
	}
	else if (func == 2)
		{
			if (shell -> pipe_count == 0)
				write(STDERR_FILENO, "exit\n", 5);
			simple_error(EXIT_FAILURE, "exit: "," too many arguments");
		}
	else
	{
		free_env(shell->env);
		shell -> env = NULL;
		free_env(shell->exp);
		shell -> exp = NULL;
		free_shell(shell);
		//system("leaks minishell");
		exit(get_status());
	}

}

