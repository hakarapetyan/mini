/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakarape <hakarape@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:24:31 by hakarape          #+#    #+#             */
/*   Updated: 2024/11/11 21:30:30 by hakarape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int is_digit(char *arg)
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
        printf("exit\nminshell: exit: %s: numeric argument required", arg);
        return (1);
        }
    }
    return (0);
    
}
int my_exit(int args, char **argv, t_shell *shell)
{
	int	i;

	i = 0;
	if (args == 1)
		return (0);
	else if (args == 2)
	{
		while (argv[i] && ft_strcmp(argv[i], "exit") == 0)
			i++;
		if (is_digit(argv[i]))
			return (1);
		else
		{
			printf("exit\n");
			return (0);
		}
	}
	else
		 return (2);
}
void execute_exit(t_shell *shell)
{
	t_commands *cmd;
	int	func;

	cmd = shell -> command;

	if (cmd && ft_strcmp(cmd -> name, "exit") == 0)
	{
		func = my_exit(shell -> token_count - 1, cmd -> args, shell);
		if(func == 1)//space count ughel
			exit(1);
		else if (func == 2)
			printf("exit\nminshell: exit: too many arguments\n");
		else
			exit(0);
	}
		
}
//skzbic qanaky nor tesaky exit echo nenie_iri
// exit exit