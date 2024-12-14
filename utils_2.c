/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:42:41 by ashahbaz          #+#    #+#             */
/*   Updated: 2024/12/14 16:15:25 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./include/minishell.h"


char	*is_key(t_shell *shell, char *need_to_be_find)
{
	env_list *node;

	node = shell -> env;
	if (!need_to_be_find || !node)
		return (NULL);
	while (node)
	{
		if (spec_strcmp(node -> key, need_to_be_find) == 0)
		{
			return (node -> value);
		}
		node = node -> next;
	}
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	str = (char *)malloc(sizeof(*s1) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (i < ft_strlen(s1))
		str[j++] = s1[i++];
	i = 0;
	while (i < ft_strlen(s2))
		str[j++] = s2[i++];
	str[j] = '\0';
	if (s1)
	{
		free(s1);
		s1 = NULL;
	}
	return (str);
}

char	*another_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	str = (char *)malloc(sizeof(*s1) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (i < ft_strlen(s1))
		str[j++] = s1[i++];
	i = 0;
	while (i < ft_strlen(s2))
		str[j++] = s2[i++];
	str[j] = '\0';
	return (str);
}

int	ft_strchr(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
char	*ft_strdup_interval(char **str,int *len)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	if (!(*str) || !(**str) || !str)
		return (NULL);
	tmp = malloc(sizeof(char) * ((*len) + 1));
	if (!tmp)
		return (NULL);
	while ((*len) > 0)
	{
		tmp[i] = str[0][j];
		j++;
		i++;
		(*len)--;
	}
	tmp[i] = '\0';
	(*str) += j;
	return (tmp);
}

int	set_state(char c, int state)
{
	if (c == '\'' && state == DEFAULT)
		state = IN_SINGLE_QUOTES;
	else if (c == '\"' && state == DEFAULT)
		state = IN_DOUBLE_QUOTES;
	else if (c == '\'' && state == IN_SINGLE_QUOTES)
		state = DEFAULT;
	else if (c == '\"' && state == IN_DOUBLE_QUOTES)
		state = DEFAULT;
	return (state);
}
