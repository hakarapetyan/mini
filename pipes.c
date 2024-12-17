/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:52:50 by ashahbaz          #+#    #+#             */
/*   Updated: 2024/12/17 18:53:12 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int create_pipes(t_shell *shell)
{
	int	i;
	int	(*fd)[2];

	i = 0;
	fd = malloc(sizeof(int[2]) * (shell -> pipe_count));
	if (!fd)
		error(ALLOCATION_ERR, shell);
	while (i < shell -> pipe_count)
	{
		if (pipe(fd[i]) == -1)
		{
			while (i > 0)
			{
				i--;
				close(fd[i][0]);
				close(fd[i][1]);
			}
			free(fd);
			return (-1);
		}
		i++;
	}
	shell -> fd = fd;
	return (0);
}


int close_pipes(t_shell *shell)
{
	int i;

	i = 0;
	while (i < shell -> pipe_count)
	{
		close(shell -> fd[i][0]);
		close(shell -> fd[i][1]);
		i++;
	}
	return (0);
}
