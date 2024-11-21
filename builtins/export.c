/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakarape <hakarape@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:38:26 by hakarape          #+#    #+#             */
/*   Updated: 2024/11/21 20:20:46 by hakarape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	my_export_helper(t_shell *shell, char **argv, int i)
{
	env_list	*exp;

	exp = shell ->exp;
	if (!exp)
	{
		printf("am i here? \n");
		exp = add_node(argv[i]);
		//return (1);
	}
	if (exp)
	{
		while (exp && exp->next)
			exp = exp->next;
		exp ->next = add_node(argv[i]);
	}
	return(0);
}
int my_export(int argc, char **arg, t_shell *shell)
{
	int	i;
	env_list *exp;

	i = 0;
	exp = shell -> exp;
	if (argc == 1)
		print_exp(shell);
	if (argc > 1)
	{
	if (arg[i] && ft_strcmp(arg[i], "export") == 0)
		i++;
	my_export_helper(shell, arg, i);
	return (0);
	}
}

int	execute_export(t_shell *shell)
{
	t_commands *cmd;

	cmd = shell -> command;

	if (cmd && ft_strcmp(cmd -> name, "export") == 0)
		if(my_export(shell -> token_count, cmd ->args, shell))
			return (1);
	return (0);
}