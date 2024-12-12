/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakarape <hakarape@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:53:50 by hakarape          #+#    #+#             */
/*   Updated: 2024/12/12 17:48:57 by hakarape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *inc_shlvl(t_shell *shell)
{
	char *value;
	int atoi;
	char *itoa;

	value = get_value(shell, "SHLVL=");
	atoi = ft_atoi(value) % 1000;
	itoa = ft_itoa(atoi + 1);
	return(itoa);
}
void chang_shlvl_in_env(t_shell *shell)
{
	env_list *list;
	char	*shlvl;

	shlvl = inc_shlvl(shell);
	list = shell->env;
	while(list)
	{
		if (ft_strcmp(list->key, "SHLVL=") == 0)
		{
			free(list->value);
			list->value=ft_strdup(shlvl);
			free(shlvl);
			return;
		}
		list = list->next;
	}
	free(shlvl);
	return ;
}

void chang_shlvl_in_exp(t_shell *shell)
{
	env_list *list;
	char	*shlvl;

	shlvl = inc_shlvl(shell);
	list = shell->exp;
	while(list)
	{
		if (ft_strcmp(list->key, "SHLVL=") == 0)
		{
			free(list->value);
			list->value=ft_strdup(shlvl);
			free(shlvl);
			return;
		}
		list = list->next;
	}
	free(shlvl);
	return ;
}