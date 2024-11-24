/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:05:24 by ashahbaz          #+#    #+#             */
/*   Updated: 2024/11/24 19:55:41 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

static	char *var_in_quotes_helper(char **str, int *len)
{
	int	i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	(*str)++;
	while ((*str)[(*len)] && (ft_isalnum((*str)[(*len)]) || (*str)[(*len)] == '_'))
		(*len)++;
	tmp = malloc(sizeof(char) * ((*len) + 1));
	if (!tmp)
		return (NULL);
	while(i != (*len))
	{
		tmp[i] = (*str)[i];
		i++;
	}
	tmp[i] = '\0';
	(*str) += (*len);
	return (tmp);
}

static char	*var_in_quotes(t_shell *shell, char **str)
{
	int len;
	char	*tmp;
	char	*res;

	len = 0;
	tmp = NULL;
	res = NULL;
	if ((*str)[len] == '$' && !((*str)[len + 1]))
	{
		(*str)++;
		return (ft_strdup("$"));
	}
	tmp = var_in_quotes_helper(str, &len);
	if (!tmp)
		return (NULL);
	res = is_key(shell -> env, tmp);
	free_arr(&tmp);
	if (!res)
		return (ft_strdup(""));
	return (ft_strdup(res));
}


static void extract_var_helper(char **str, int *i, char **res, char **tmp)
{
	while ((*str)[*i] && (*str)[*i] != '$')
		(*i)++;
	*tmp = ft_strdup_interval(str, i);
	*res = ft_strjoin(*res, *tmp);
	free(*tmp);
	*tmp = NULL;

}
char	*extract_var_from_quoted_str(char *str, t_shell *shell)
{
	char	*res;
	char	*tmp;
	int		i;

	i = 0;
	res = NULL;
	tmp = NULL;
	if (!shell -> env || !str)
		return (NULL);
	while (*str)
	{
		if (str[i] != '$')
			extract_var_helper(&str, &i, &res, &tmp);
		else if(str[i] == '$' && !is_quote(str[i + 1]))
		{
			tmp = var_in_quotes(shell, &str);
			res = ft_strjoin(res, tmp);
			free(tmp);
			tmp = NULL;
		}
	}
	return (res);
}
