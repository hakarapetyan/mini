/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakarape <hakarape@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:24:31 by hakarape          #+#    #+#             */
/*   Updated: 2024/12/02 14:11:55 by hakarape         ###   ########.fr       */
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
        	printf("exit\nminishell: exit: %s: numeric argument required\n", arg);
        	return (1);
        }
    }
    return (0);
}
// long	ft_atoi(char *str)
// {
// 	int		i;
// 	int		sign;
// 	long	result;

// 	i = 0;
// 	sign = 1;
// 	result = 0;
// 	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
// 		i++;
// 	if (str[i] == '-')
// 		sign = -1;
// 	if (str[i] == '+' || str[i] == '-')
// 		i++;
// 	while (str[i] >= '0' && str[i] <= '9')
// 	{
// 		result = result * 10 + (str[i] - 48);
// 		i++;
// 	}
// 	if (str[i] || str[i - 1] == '-' || str[i - 1] == '+')
// 	{
// 		ft_error("IS NOT ONLY DIGIT\n");
// 		return (0);
// 	}
// 	return (result * sign);
// }
static int	check_int(char *arg)
{
	printf("arg=%c\n", *arg);
	printf("argum=%s\n", arg);
	if (ft_strcmp(arg, INT_MAX_8) > 0 || (ft_strcmp(arg, INT_MIN_8) > 0 && *arg == '-'))
	{
		printf("good\n");
		printf("exit\nminishell: exit: %s: numeric argument required\n", arg);
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
		if (check_int(argv[i]))
			return (1);
		else if(is_digit(argv[i]))
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
		exit(1);
	else if (func == 2)
		printf("exit\nminshell: exit: too many arguments\n");
	else
		exit(0);	
}

