/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakarape <hakarape@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:53:50 by hakarape          #+#    #+#             */
/*   Updated: 2024/12/17 13:04:51 by hakarape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


char *inc_shlvl(t_shell *shell)
{
	char *value;
	int atoi;
	char *itoa;

	value = get_value(shell, "SHLVL=");
	if (!value)
		atoi = 0;
	else
		atoi = ft_atoi(value) % 1000;
	itoa = ft_itoa(atoi + 1);
	return(itoa);
}


static void add_shlvl(t_shell *shell,char *shlvl)
{
	env_list *list;
	env_list *new;

	list = shell -> env;
	new = malloc(sizeof(env_list));
	new -> key = ft_strdup("SHLVL=");
	new -> value = ft_strdup(shlvl);
	while (list -> next) 
		list = list -> next;
	list -> next = new;
	new -> next = NULL;
}
void chang_shlvl_in_env(t_shell *shell)
{
	env_list *list;
	char	*shlvl;

	shlvl = inc_shlvl(shell);
	list = shell->env;
	if (!check_key(list, "SHLVL="))
		add_shlvl(shell,shlvl);
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