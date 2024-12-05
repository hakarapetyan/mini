/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakarape <hakarape@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:32:26 by hakarape          #+#    #+#             */
/*   Updated: 2024/12/05 19:51:40 by hakarape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	builtins(t_shell *shell)
{
	t_commands *cmd;

	cmd = shell -> command;
	if (cmd && ft_strcmp(cmd -> name, "pwd") == 0)
	{
		if(my_pwd(shell))
		return (1);
	}
	else if (cmd && ham_strcmp(cmd -> name, "echo") == 0)
		my_echo(shell -> token_count, cmd -> args);
	else if (cmd && ft_strcmp(cmd -> name, "exit") == 0)
		execute_exit(shell);
	else if (cmd && ft_strcmp(cmd -> name, "env") == 0)
	{
		if(my_env(shell -> token_count, shell, cmd->args))
			return (1);
	}
	else if (cmd && ft_strcmp(cmd -> name, "export") == 0)
	{
		if(my_export(shell -> token_count, cmd ->args, shell))
			return (1);
	}
	else if (cmd && ft_strcmp(cmd -> name, "unset") == 0)
	{
		if(my_unset(shell -> token_count, cmd -> args, shell))
			return(1);
	}
	else if(cmd && ft_strcmp(cmd -> name, "cd") == 0)
	{
		if (my_cd(shell -> token_count, cmd -> args, shell))
			return (1);
	}
	return (0);
}
