/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakarape <hakarape@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:32:26 by hakarape          #+#    #+#             */
/*   Updated: 2024/12/18 19:12:08 by hakarape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int builtins_helper(t_shell *shell, t_commands *command, char *name)
{
	if (command && ft_strcmp(name, "env") == 0)
	{
		if(my_env(command -> arg_count, shell, command->args))
			return (1);
	}
	else if (command && ft_strcmp(command -> name, "export") == 0)
	{
		if(my_export(command -> arg_count, command ->args, shell))
			return (1);
	}
	else if (command && ft_strcmp(command -> name, "unset") == 0)
	{
		if(my_unset(command -> arg_count, command -> args, shell))
			return(1);
	}
	else if(command && ft_strcmp(command -> name, "cd") == 0)
	{
		if (my_cd(command -> arg_count, command -> args, shell))
			return (1);
	}
}
int	builtins(t_shell *shell, t_commands * command)
{
	char *name;

	name = ft_tolower(command -> name);
	set_status(0);
	if (command && ft_strcmp(name, "pwd") == 0)
	{
		if(my_pwd(shell))
		return (1);
	}
	else if (command && ham_strcmp(name, "echo") == 0)
		my_echo(command -> arg_count, command -> args);
	else if (command && ft_strcmp(command -> name, "exit") == 0)
		execute_exit(shell, command);
	else if (builtins_helper(shell, command, name))
		return (1);
	return (0);
}
