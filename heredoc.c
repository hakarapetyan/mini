/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakarape <hakarape@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 15:52:37 by ashahbaz          #+#    #+#             */
/*   Updated: 2024/12/08 16:53:09 by hakarape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./include/minishell.h"


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
		while (1)
		{
			delimiter = readline("> ");
			// if (delimiter != NULL && get_status() == 1 )  
			// {
			// 	printf("barev aper\n");
			// 	shell -> heredoc_flag = 1;
			// //	set_status(247);
			// 	free(delimiter);
			// 	delimiter = NULL;
			// 	break;
			// }
			if (ft_strcmp(delimiter, cmd -> r_heredoc) == 0 || get_status() == 1)
			{
				free(delimiter);
				delimiter = NULL;
				break;
			}
			if (get_status() == 1)
				return (0);
			if (cmd -> state == DEFAULT)
				delimiter = extract_var_from_quoted_str(delimiter, shell);
			write(fd, delimiter, ft_strlen(delimiter));
			write(fd, "\n", 1);
			free(delimiter);
			delimiter = NULL;
		}
		close(fd);
	}
	return (0);
}
