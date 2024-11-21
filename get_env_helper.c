/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakarape <hakarape@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:52:10 by hakarape          #+#    #+#             */
/*   Updated: 2024/11/21 20:57:12 by hakarape         ###   ########.fr       */
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
	return (env);
}
char **list_to_arr(env_list *list)
{
	int size;
	//env_list *env;
	char **arr;
	char *tmp;
	char *cmp;

	size =0 ;
	//env = shell->env;
	if(!list)
		return (NULL);
	size = ft_lstsize(list);
	arr = (char **)malloc(sizeof(char*) * (size + 1));
	if(!arr)
		return (NULL);
		size = 0;
	while (list)
	{
		tmp = ft_strjoin(list ->key, "=");
		cmp = ft_strjoin(tmp, list-> value);
		arr[size] = cmp;
		size++;
		//free(cmp);
		list = list ->next;
	}
	 size=0;
	while (arr[size])
	{
		printf("arr=%s\n", arr[size]);
		size++;
	}
	arr[size] = NULL;
	return (arr);
}
// char **list_to_arr(env_list *list)
// {
//     int size;
//     char **arr;
//     char *tmp;
//     char *cmp;
//     env_list *current;

//     if (!list)
//         return (NULL);

//     // Get the size of the list.
//     size = ft_lstsize(list);
//     arr = (char **)malloc(sizeof(char *) * (size + 1));
//     if (!arr)
//         return (NULL);

//     size = 0;
//     current = list;
//     while (current)
//     {
//         tmp = ft_strjoin(current->key, "="); // Join key with "=".
//         if (!tmp)
//         {
//             // Free previously allocated memory in case of failure.
//             while (size > 0)
//                 free(arr[--size]);
//             free(arr);
//             return (NULL);
//         }

//         cmp = ft_strjoin(tmp, current->value); // Join "key=" with value.
//         free(tmp); // Free intermediate result.
//         if (!cmp)
//         {
//             // Free previously allocated memory in case of failure.
//             while (size > 0)
//                 free(arr[--size]);
//             free(arr);
//             return (NULL);
//         }

//         arr[size] = cmp; // Add the complete string to the array.
//         size++;
//         current = current->next; // Move to the next list node.
//     }

//     arr[size] = NULL; // Null-terminate the array.

//     return arr;
// }

char **sorting_for_export(env_list *current)
{
	char **envir;
	char **export;
	//current = shell->exp;
	export = list_to_arr(current);
	envir = ascii_sort_env(export);
	while (current)
	{
		printf("sorting=%s\n", current->key);
		current = current->next;
	}
	int i = 0;
	while (export[i])
	{
		printf("am i good-x %s\n", export[i]);
		i++; 
	}
	return (envir);
}