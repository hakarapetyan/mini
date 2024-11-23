/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakarape <hakarape@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 15:51:03 by hakarape          #+#    #+#             */
/*   Updated: 2024/11/23 16:58:39 by hakarape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int my_pwd(t_shell *shell)
{
	char *cmd;

	cmd = getcwd(NULL, 0);
	if(cmd != NULL)
	{
		printf("%s\n", cmd);
		free(cmd);
		return (0);
	}
	else
	{
		printf("error with memory allocation\n");
		return (1);
	}
}
int	execute_pwd(t_shell *shell)
{
	t_commands *cmd;

	cmd = shell -> command;
	if (cmd && ft_strcmp(cmd -> name, "pwd") == 0)
		if(my_pwd(shell))
			return (1);
		return(0);
		
}