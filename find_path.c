/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakarape <hakarape@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 15:51:46 by ashahbaz          #+#    #+#             */
/*   Updated: 2024/12/18 20:39:24 by hakarape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

static void free_path(char **arr)
{

    int i = 0;

    if (arr == NULL || *arr == NULL)
        return;

    while ((arr)[i])
    {
        free((arr)[i]);
        (arr)[i] = NULL;
        i++;
    }
    free(arr);
	arr = NULL;
}

static char	**find_path_from_env(t_shell *shell)
{
	char		**path;
	char	*key;

	key = NULL;
	path = NULL;

	if (!(shell -> env))
		return (NULL);
	key = is_key(shell, "PATH");
	if (!key)
		return (NULL);
	path = ft_split(key, ':');
	return (path);
}

char	*find_path(t_shell *shell, char	*command_name)
{
	char	**path;
	char	*tmp;
	char	*tmp2;
	int		i;

	i = 0;
	if (!command_name)
		return (NULL);
	path = find_path_from_env(shell);
	if (!path)
		return (NULL);
	while (path[i])
	{
		tmp = another_strjoin(path[i], "/");
		tmp2 = ft_strjoin(tmp,command_name);
		 if (tmp2 && access(tmp2,X_OK | F_OK) == 0)
		{
			free_path(path);
			return (tmp2);
		}
		i++;
		free_arr(&tmp2);
	}
	free_path(path);
	return (NULL);
}
