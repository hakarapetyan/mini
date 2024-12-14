/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:33:30 by hakarape          #+#    #+#             */
/*   Updated: 2024/12/14 17:23:52 by ashahbaz         ###   ########.fr       */
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
		free(cmd);
		error(GETCWDERROR, shell);
		//printf("error with memory allocation\n");
		return (1);
	}
}
