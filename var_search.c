/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_search.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:00:55 by ashahbaz          #+#    #+#             */
/*   Updated: 2024/11/24 16:04:28 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

static int is_key_helper(t_shell *shell, char **tmp)
{
	if (is_key(shell -> env, *tmp))
	{
		free_arr(tmp);
		return(1);
	}
	else
	{
		free_arr(tmp);
		return (2);
	}
}

static int is_valid_var(char **str,t_shell *shell, int i)
{
	char	*tmp;

	tmp = NULL;
	while ((*str)[i])
	{
		while (*(*str) != '$' && *(*str))
			(*str)++;
		if (!(*str) || !(**str))
			break;
		(*str)++;
		if (!(*str) || !(**str))
			break;
		while ((*str)[i] && !is_space((*str)[i]) && (*str)[i] != '$' && !is_quote((*str)[i]) && !is_separator((*str)[i]))
		{
			i++;
		}
		tmp = ft_strdup_interval(str, &i);
		return(is_key_helper(shell, &tmp));
	}
	free_arr(&tmp);
	return (0);
}

int	 var_search(char	*str, t_shell *shell)
{
	int	i;
	int val;

	i = 0;
	val = 0;
	if (!(shell -> env) || !str)
		return (0);
	if(ft_strchr(str, '$'))
	{
		val = is_valid_var(&str, shell, i);
		if (val == 1)
			return (1);
		else if (val == 2)
			return (2);
	}
	return (0);
}
