/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakarape <hakarape@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:32:36 by hakarape          #+#    #+#             */
/*   Updated: 2024/12/05 14:32:36 by hakarape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void changes_in_list(env_list *list, char *pwd, const char *key)
{
	while (list)
	{
		if (ft_strcmp(list ->key, key) == 0)
		{	
			free_str(list -> value);
			list -> value = ft_strdup(pwd);
		}
		list = list -> next;	
	}
}
char *get_value(t_shell *shell, char *key)
{
	env_list *env;

	env = shell -> env;
	if (!(*key) || !key)
		return (NULL);
	while (env)
	{
		if (ft_strcmp(env ->key, key) == 0)
		{
			if (!env->value)
				return(NULL);
			return (env ->value);
		}
		env = env->next;
	}
	return (NULL);
}
