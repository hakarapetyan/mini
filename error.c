/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 15:52:08 by ashahbaz          #+#    #+#             */
/*   Updated: 2024/12/14 16:11:21 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./include/minishell.h"

void	error(char	*err, t_shell *shell)
{
	printf("%s\n", err);
	(void)shell;
	//free_shell(shell);
	// system("leaks minishell");
	//exit(1);
}


static void which_errno(void)
{
	// int status;

	// status = 127;
	if (errno == ENOENT)
	{
		write(STDERR_FILENO, NO_SUCH_FILE_MSG, ft_strlen(NO_SUCH_FILE_MSG));
		set_status(127);
	}
	else if (errno == EACCES)
	{
		write(STDERR_FILENO, PERMISSION_DENIED_MSG, ft_strlen(PERMISSION_DENIED_MSG));
		set_status(126);
	}
	else if (errno == EISDIR)
	{
		write(STDERR_FILENO, IS_DIRECTORY_MSG, ft_strlen(IS_DIRECTORY_MSG));
		set_status(126);
	}
	else if (errno == ENOTDIR)
	{
		write(STDERR_FILENO, NOT_DIRECTORY_MSG, ft_strlen(NOT_DIRECTORY_MSG));
		set_status(1);
	}
	//set_status(status);
}


void	error_message(int status, char *command_name)
{
	// set_status(status);
	(void)status;
	if (command_name)
	{
		write(STDERR_FILENO, "minishell: ", 11);
		write(STDERR_FILENO, command_name, ft_strlen(command_name));
		write(STDERR_FILENO, ": ", 2);
		which_errno();
	}
	write(STDERR_FILENO, "\n", 1);
	return ;
}

void	simple_error(int status, char *command_name, char *message)
{
	set_status(status);
	if (command_name)
	{
		write(STDERR_FILENO, "minishell: ", 11);
		if (command_name)
		{
			write(STDERR_FILENO, command_name, ft_strlen(command_name));
			write(STDERR_FILENO, ": ", 2);
		}
		write(STDERR_FILENO, message, ft_strlen(message));
	}
	write(STDERR_FILENO, "\n", 1);
	return ;
}

void	syntax_error(char *message)
{
	char	*str;

	str = "syntax error near unexpected token `";
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, message, ft_strlen(message));
	write(STDERR_FILENO, "'\n", 2);
	set_status(2);
	return ;
}
