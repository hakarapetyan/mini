/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 15:53:04 by ashahbaz          #+#    #+#             */
/*   Updated: 2024/11/24 15:53:05 by ashahbaz         ###   ########.fr       */
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
	shell -> next = NULL;
	shell -> token = NULL;
	shell -> command = NULL;
	// init_data(&shell -> env);
	// init_data(&shell -> exp);
}

