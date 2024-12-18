/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakarape <hakarape@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:05:24 by ashahbaz          #+#    #+#             */
/*   Updated: 2024/12/18 20:11:22 by hakarape         ###   ########.fr       */
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
static int only_dollar(char **str, char **res, int *len)
{
	int flag;

	flag = 0;
	while ((*str)[*len] && (*str)[*len] == '$')
	{
		(*len)++;
	}
	if ((*str)[*len] == '\0' || is_space((*str)[*len]))
	{
		*res = ft_substr(*str, 0, *len);
		(*str)+= *len;
		flag = 1;
	}
	return (flag);
}
static char	*var_in_quotes(t_shell *shell, char **str)
{
	int		len;
	char	*tmp;
	char	*res;

	len = 0;
	tmp = NULL;
	res = NULL;
	if ((*str)[len] == '$' && ((*str)[len + 1]) && ((*str)[len + 1]) == '?')
	{
		(*str) += 2;
		return (ft_itoa(get_status()));//freeeee itoa
	}
	if ((*str)[len] == '$')
	{
		if (only_dollar(str, &res, &len) == 1)
			return (res);
	}
	tmp = var_in_quotes_helper(str, &len);
	if (!tmp)
		return (NULL);
	res = is_key(shell, tmp);
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
	free_str(*tmp);

}
char	*extract_var(char *str, t_shell *shell)
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
			free_str(tmp);
		}
	}
	return (res);
}
