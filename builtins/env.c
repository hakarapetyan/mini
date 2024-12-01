/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakarape <hakarape@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 14:14:20 by hakarape          #+#    #+#             */
/*   Updated: 2024/11/24 16:12:51 by hakarape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int my_env(int argc,t_shell *shell, char **argv)
{
	int	i;

	i = 0;
	if (argc == 1)
		 print_env(shell);
	if (argc > 1)
	{
		if (argv[i] && (!ft_strcmp(argv[i], "env")))
			i++;
		ft_putendl_fd("env: setenv ", 2);
		ft_putendl_fd(argv[i], 2);
		ft_putendl_fd(": Invalid argument\n", 2);
		return (1);
	}
	return (0);
}
// int	execute_env(t_shell *shell)
// {
// 	t_commands *cmd;

// 	cmd = shell -> command;
// 	if (cmd && ft_strcmp(cmd -> name, "env") == 0)
// 		if(my_env(shell -> token_count, shell, cmd->args))
// 		return (1);
// 	return (0);
// }