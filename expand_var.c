/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:43:36 by ashahbaz          #+#    #+#             */
/*   Updated: 2024/11/24 16:43:37 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./include/minishell.h"

void	expand_var(t_shell *shell)
{
    t_token *current;
	//char	*tmp;
    char	*key;

	if (!shell -> env)
		return ;
    current = shell->token;
    key = NULL;
    while (current)
    {
        if (current->type == ENV_VAR)
        {
			//printf("{%s}\n",current -> value);
			key = is_key(shell->env, current->value);
            if (key)
			{
				current -> var_value = ft_strdup(getenv(key));
			//	current -> var_value = add_space_to_env_var(current -> value, tmp);
			}
        }
        current = current->next;
    }
}
