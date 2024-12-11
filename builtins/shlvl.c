/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakarape <hakarape@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:53:50 by hakarape          #+#    #+#             */
/*   Updated: 2024/12/11 21:35:33 by hakarape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"



char *inc_shlvl(t_shell *shell)
{
	char *value;
	int atoi;
	char *itoa;

	value = get_value(shell, "SHLVL=");
	printf("value%s\n", value);
	atoi = ft_atoi(value);
	itoa = ft_itoa(atoi + 1);
	return(itoa);
}
void chang_shlvl(t_shell *shell)
{
	env_list *list;
	env_list *tmp;
	char	*shlvl;

	shlvl = inc_shlvl(shell);
	printf("%s\n",shlvl);
	list = shell->env;
	if (!ft_strcmp(shell -> input, "./minishell"))
	{
		tmp = list;
		while(list)
		{
			printf("1list->value=%s\n", list->value);
				printf("1tmp->value=%s\n", tmp->value);
			if (check_key(tmp, "SHLVL"))
			{
				printf("list->value=%s\n", list->value);
				printf("tmp->value=%s\n", tmp->value);
				free(list->value);
				list->value=ft_strdup(shlvl);
				free(shlvl);
				return;
			}
			list = list->next;
		}
	}
	free(shlvl);
	return ;
}