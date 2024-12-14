/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 15:52:37 by ashahbaz          #+#    #+#             */
/*   Updated: 2024/12/14 16:55:50 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./include/minishell.h"


static void heredoc_helper(t_shell *shell, t_commands *cmd, char *delimiter, int fd)
{
	while (1)
	{
		delimiter = readline("> ");
		if (delimiter != NULL && get_status() == 222)
		{
			free(delimiter);
			delimiter = NULL;
			break;
		}
		if (ft_strcmp(delimiter, cmd -> r_heredoc) == 0 || (!(delimiter) && get_status() == 1))
		{
			free(delimiter);
			delimiter = NULL;
			break;
		}
		if (cmd -> state == DEFAULT)
			delimiter = extract_var_from_quoted_str(delimiter, shell);
		write(fd, delimiter, ft_strlen(delimiter));
		write(fd, "\n", 1);
		free(delimiter);
		delimiter = NULL;
	}
}

int heredoc_handle(t_shell *shell)
{
	t_commands *cmd = shell -> command;
	char	*delimiter;
	int fd = 0;

	delimiter = NULL;
	if (cmd -> r_heredoc)
	{
		fd = open("tmp_file", O_WRONLY | O_CREAT | O_TRUNC, 0600);
		signals(HEREDOC);
		heredoc_helper(shell, cmd, delimiter , fd);
		close(fd);
	}
	return (0);
}
