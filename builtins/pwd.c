/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakarape <hakarape@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:33:30 by hakarape          #+#    #+#             */
/*   Updated: 2024/12/17 13:37:15 by hakarape         ###   ########.fr       */
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
		//error(GET_CWD_ERROR, shell);
		//printf("error with memory allocation\n");
		return (1);
	}
}
