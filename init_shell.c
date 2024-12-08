/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakarape <hakarape@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 15:53:04 by ashahbaz          #+#    #+#             */
/*   Updated: 2024/12/08 15:59:16 by hakarape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./include/minishell.h"

void	init_data(env_list **data)
{
	(*data) -> key = NULL;
	(*data) -> value = NULL;
	(*data) -> next = NULL;
}
void	init_shell(t_shell *shell)
{
	shell -> pwd = NULL;
	shell -> oldpwd = NULL;
	shell -> input = NULL;
	shell -> env = NULL;
	shell -> exp = NULL;
	shell -> shlvl = 0;
	shell -> token_count = 0;
	shell -> flag = 0;
	shell -> heredoc_flag = 0;
	shell -> next = NULL;
	shell -> token = NULL;
	shell -> command = NULL;
	//dup(STDIN_FILENO);
	//dup(STDOUT_FILENO);
	// init_data(&shell -> env);
	// init_data(&shell -> exp);
}

