/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_environment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:31:04 by hakarape          #+#    #+#             */
/*   Updated: 2024/12/14 16:42:42 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

char	*get_the_key(char *str)
{
	char *key;
	int		i;

	key = NULL;
	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '=')
		i++;
	key = malloc(sizeof(char) * (i + 2));
	if (!key)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		key[i] = str[i];
		i++;
	}
	if (str[i])
		key[i++] = '=';
	//i++;
	key[i] = '\0';
	return (key);
}

char	*get_the_value(char *str)
{
	char *value;
	int	i;

	value = NULL;
	i = 0;
	if (!str || !ft_strchr(str, '='))
		return (NULL);
	while (*str)
		str++;
	while (*str != '=')
	{
		str--;
		i++;
	}
	value = malloc (sizeof(char) * (i + 1));
	if (!value)
		return (NULL);
	i = 0;
	while (str[i])
	{
		value[i] = str[i + 1];
		i++;
	}
	value[i] = '\0';
	//printf("vaue=\n", value);
	return (value);
}

void	get_env_list(t_shell **shell, char *str)
{
	env_list *current;

	if (!str)
		return ;
	if (!(*shell) -> env)
		(*shell) -> env = add_node(str);
	else
	{
		 current = (*shell)->env;
        while (current -> next)
            current = current -> next;
        current -> next = add_node(str);
	}
}
void	get_exp_list(t_shell **shell, char *str)
{
	env_list *current;

	if (!str)
		return ;
	if (!(*shell) -> exp)
	{
		(*shell) -> exp = add_node(str);
	}
	else
	{
		 current = (*shell) -> exp;
        while (current -> next)
            current = current -> next;
        current -> next = add_node(str);
	}
}

static void norm_get_env(char *env, t_shell *shell, int *i)
{
	if (spec_strcmp(env, "OLDPWD=") == 0)
	{
		get_exp_list(&shell, "OLDPWD");
		(*i)++;
	}
}
void	get_environment(t_shell *shell, char **env)
{
	// char **envir;
	int	i;

	i = 0;
	if (!(shell -> env))
	{
		while (env[i])
		{
			if (spec_strcmp(env[i], "OLDPWD=") == 0)
				i++;
			get_env_list(&shell, env[i]);
			i++;
		}
	}
	if (!(shell -> exp))
	{
		i = 0;
		while (env[i])
		{
			norm_get_env(env[i], shell, &i);
			get_exp_list(&shell, env[i]);
			i++;
		}
	}
}
