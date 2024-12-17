/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:32:56 by hakarape          #+#    #+#             */
/*   Updated: 2024/12/17 19:55:39 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int my_env(int argc,t_shell *shell, char **argv)
{
	int	i;

	i = 0;
	if (argc == 1 && shell -> env != NULL)
		 print_env(shell);
	if (argc > 1)
	{
		if (argv[i] && (!ft_strcmp(argv[i], "env")))
			i++;
		error_message(CMD_NOT_FOUND, argv[i]);
		//simple_error(EXIT_FAILURE, argv[i], "Invalid argument");
		// ft_putendl_fd("env: ", 2);
		// ft_putendl_fd(argv[i], 2);
		// ft_putendl_fd(": Invalid argument\n", 2);
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
