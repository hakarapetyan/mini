/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:52:10 by hakarape          #+#    #+#             */
/*   Updated: 2024/12/03 20:35:25 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

env_list	*add_node(char *str)
{
	env_list	*node;

	node = malloc(sizeof(env_list));
    if (!node)
	{
        free(node);
        node = NULL;
		return (NULL);
    }
	node -> key = get_the_key(str);
	node -> value = get_the_value(str);

	// printf("vlll=%s\n", node->key);
	// if (!node -> key || !node -> value)
	// 	{
	// 		free (node -> key);
	// 		free (node -> value);
	// 		free (node);
	// 		node = NULL;
	// 		printf("boom\n");
	// 		//system("leaks minishell");
	// 		return (NULL);
 	// 	}
	node -> next = NULL;
	return (node);
}
char	**ascii_sort_env(char **env)
{
	int	i;
	int	j;
	char *tmp;

	i = 0;
	j = 0;
	tmp = NULL;
	if (!env)
		return (NULL);
	while (env[i])
	{
		j = 0;
		while (env[j])
		{
			if (spec_strcmp(env[i], env[j]) < 0)
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
			j++;
		}
		i++;
	}
	// printf("hihi\n");
	return (env);
}
char **list_to_arr(env_list *list)
{
	int size;
	char **arr;
	char *cmp;

	size = 0;
	if(!list)
		return (NULL);
	size = ft_lstsize(list);
	arr = (char **)malloc(sizeof(char*) * (size + 1));
	if(!arr)
		return (NULL);
	size = 0;
	while (list)
	{
		if (!list->value)
			list->value = ft_strdup("");
		cmp = another_strjoin(list ->key, list-> value);
		arr[size] = cmp;
		size++;
		list = list ->next;
	}
	// if(cmp)
	// 	free(cmp);
	arr[size] = NULL;
	return (arr);
}
char **sorting_for_export(env_list *current)
{
	char **envir;
	char **export;

	export = list_to_arr(current);
	envir = ascii_sort_env(export);
	return (envir);
}
