/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 15:52:37 by ashahbaz          #+#    #+#             */
/*   Updated: 2024/12/11 18:35:40 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./include/minishell.h"


int heredoc_handle(t_shell *shell,t_commands *cmd)
{
	//t_commands *cmd = shell -> command;
	char	*delimiter;
	int fd = 0;

	delimiter = NULL;
	if (cmd -> r_heredoc)
	{
		fd = open("tmp_file", O_WRONLY | O_CREAT | O_TRUNC, 0600);
		while (1)
		{
			delimiter = readline("> ");
			if (ft_strcmp(delimiter, cmd -> r_heredoc) == 0)
			{
				free(delimiter);
				delimiter = NULL;
				break;
			}
			if (cmd -> state == DEFAULT)
				delimiter = extract_var(delimiter, shell);
			write(fd, delimiter, ft_strlen(delimiter));
			write(fd, "\n", 1);
			free(delimiter);
			delimiter = NULL;
		}
		close(fd);
	}
	return (0);
}
