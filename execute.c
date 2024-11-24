/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:43:43 by ashahbaz          #+#    #+#             */
/*   Updated: 2024/11/24 19:55:55 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./include/minishell.h"


// static void execute_builtins(t_shell *shell)
// {
// 	char	*cmd;

// 	cmd = shell -> command -> name;
// 	if (!ft_strcmp(cmd,"echo"))
// 		execute_echo(shell);
// }
static int ft_open(char *redir, int flag, int permission)
{
	int fd;

	fd = open(redir, flag, permission);
	if (fd < 0)
	{
	if (errno == EACCES)
		printf("permission denied\n");
		return (-1);
	}
	return (fd);
	//__err_msg_prmt__(path, ": Permission denied", INV_ARG);
	// else if (errno == ENOENT)
	// __err_msg_prmt__(path, ": No such file or directory", INV_ARG);
	// else if (errno == EISDIR)
	// __err_msg_prmt__(path, ": is a directory", INV_ARG);
}
static void	prepare_redirections(t_shell *shell, char **pathname)
{
	if (shell->command->r_heredoc)
	{
		shell->command->fd_in = open("tmp_file", O_RDONLY);
		if (shell->command->fd_in < 0)
		{
			free(*pathname);
			error_message(1, "tmp_file");
			///exit(EXIT_FAILURE);
		}
	}
	else if (shell->command->r_in)
	{
		shell->command->fd_in = open(shell->command->r_in, O_RDONLY);
		if (shell->command->fd_in < 0) {
			free(*pathname);
			error_message(1, shell->command->r_in);
			//exit(EXIT_FAILURE);
		}
	}
	if (shell->command->fd_in >= 0)
	{
		if (dup2(shell->command->fd_in, STDIN_FILENO) < 0)
		{
			free(*pathname);
			error_message(1, "dup2 error");
			close(shell->command->fd_in);
			//exit(EXIT_FAILURE);
		}
    	close(shell->command->fd_in);
	}
	if (shell->command->is_append)
		shell->command->fd_out = open(shell->command->r_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (shell->command->r_out)
	{
		shell->command->fd_out = open(shell->command->r_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (shell->command->fd_out < 0)
		{
			free(*pathname);
			error_message(1, shell -> command -> r_out);
			// if (pathname)
			// free(pathname);
			//exit(EXIT_FAILURE);
		}
		if (shell->command->fd_out >= 0)
		{
			if (dup2(shell->command->fd_out, STDOUT_FILENO) < 0)
			{
				free(*pathname);
				error_message(1, shell -> command -> r_out);
				close(shell->command->fd_out);
				// if (pathname)
				// free(pathname);
				//exit(EXIT_FAILURE);
			}
			close(shell->command->fd_out);
		}
	}
}
static void run_execve(t_shell *shell, char **pathname)
{
	//printf("[%s]\n",shell -> command -> args[1]);
	if (execve(*pathname, shell->command->args, NULL) == -1)
	{
		perror("execve failed");
		if (*pathname)
			free(*pathname);
		//free_path
		exit(EXIT_FAILURE);
	}
}
static void execute_execve(t_shell *shell, char **pathname)
{
    pid_t pid;

    pid = fork();
    if (pid == 0)
    {
        prepare_redirections(shell, pathname);
		run_execve(shell, pathname);
    }
    else if (pid > 0)
        wait(NULL);
    else
        error_message(1, "fork failed");
	// if (pathname)
    // 	free(pathname);
}



void static single_redir_file(t_shell *shell)
{
	if (shell->command->r_in || shell -> command ->r_heredoc)
	{
		shell->command->fd_in = open(shell->command->r_in, O_RDONLY);
		if (shell->command->fd_in < 0)
		{
			error_message(1, shell -> command -> r_in);
		}
		close(shell->command->fd_in);
	}
	if (shell->command->is_append)
		shell->command->fd_out = open(shell->command->r_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (shell->command->r_out)
	{
		shell->command->fd_out = ft_open(shell->command->r_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (shell->command->fd_out < 0)
		{
			error_message(1, shell -> command -> r_out);
		}
		close(shell->command->fd_out);
	}
}





void execute_command(t_shell *shell)
{
	char *pathname;

	pathname = NULL;
	if (!(shell -> command -> name))
	{
		single_redir_file(shell);
		return;
	}
	if (access(shell -> command -> name,X_OK || F_OK) == 0)
	{
		pathname = shell -> command -> name;
		execute_execve(shell, &pathname);
		// if (execute_execve(shell, pathname) == -1)
		// {
		// 	simple_error(1 , pathname , "Execve failed");
		// 	//freeeee_shell
		// 	return ;
		// }
	}
	else
	{
		pathname = find_path(shell, get_last_command(shell)->name);
		if (!pathname)
		{
			simple_error(CMD_NOT_FOUND, get_last_command(shell)->name, "command not found");
			return;
		}
		execute_execve(shell, &pathname);

		//if (execute_execve(shell, pathname) == -1)
		// {
		// 	simple_error(1 , pathname , "Execve failed");
		// 	return ;
		// }
	}
		if (pathname)
			free(pathname);
}


int	is_builtin(char *name)
{
	if (!ft_strcmp(name, "echo"))
		return (1);
	else if (!ft_strcmp(name , "pwd"))
		return (1);
	else if (!ft_strcmp(name , "cd"))
		return (1);
	else if (!ft_strcmp(name , "env"))
		return (1);
	else if (!ft_strcmp(name , "export"))
		return (1);
	else if (!ft_strcmp(name , "exit"))
		return (1);
	else
		return (0);
}
