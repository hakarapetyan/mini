/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dups.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:44:34 by ashahbaz          #+#    #+#             */
/*   Updated: 2024/12/17 18:52:29 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

static void	dup_first(t_shell *shell)
{
	if (dup2(shell->fd[0][1], 1) == -1)
	{
		close_pipes(shell);
		printf("pipe dup failed\n");
		clean_shell_exit(shell, 1);
	}
}
static void	dup_last(t_shell *shell)
{
	if (dup2(shell->fd[shell->pipe_index - 1][0], 0) == -1)
	{
		close_pipes(shell);
		printf("pipe dup failed\n");
		clean_shell_exit(shell, 1);
	}
}

static void	dup_middle(t_shell *shell)
{
	if (dup2(shell->fd[shell->pipe_index - 1][0], 0) == -1)
	{
		close_pipes(shell);
		printf("pipe dup failed\n");
		clean_shell_exit(shell, 1);
	}
	if (dup2(shell->fd[shell->pipe_index][1], 1) == - 1)
	{
		close_pipes(shell);
		printf("pipe dup failed\n");
		clean_shell_exit(shell, 1);
	}
}
void dups(t_shell *shell)
{
	if (shell->pipe_index == 0)
		dup_first(shell);
	else if (shell->pipe_index == shell->pipe_count)
		dup_last(shell);
	else
		dup_middle(shell);
	close_pipes(shell);
}
