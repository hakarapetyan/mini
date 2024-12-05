/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:43:43 by ashahbaz          #+#    #+#             */
/*   Updated: 2024/12/05 20:41:18 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./include/minishell.h"


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

static void run_execve(t_shell *shell, char **pathname)
{
	if (execve(*pathname, shell->command->args,NULL) == -1)
	{
		perror("execve failed");
		if (*pathname)
			free(*pathname);
		//free_path
		//exit(EXIT_FAILURE);
	}
}
static void execute_execve(t_shell *shell, char **pathname)
{
    pid_t pid;
	int status;

    pid = fork();
    if (pid == 0)
    {
    	//if (prepare_redirections(shell) >= 0)
			run_execve(shell, pathname);
    }
    else if (pid > 0)
	{
        waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			set_status(WEXITSTATUS(status));
	}
    else
	{
        error_message(1, "fork failed");
	}
	free(*pathname);
	*pathname = NULL;
}



int single_redir_file(t_commands *command)
{
	if (command->r_in)
	{
		command->fd_in = open(command->r_in, O_RDONLY);
		if (command->fd_in < 0)
		{
			error_message(1, command -> r_in);
			return (-1);
		}
		close(command->fd_in);
	}
	if (command->is_append)
		command->fd_out = open(command->r_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (command->r_out)
	{
		command->fd_out = ft_open(command->r_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (command->fd_out < 0)
		{
			error_message(1, command -> r_out);
			return (-1);
		}
		close(command->fd_out);
	}
	return (0);
}


static void handle_builtin(t_shell *shell)
{
	printf("hasar?\n");
    // int original_stdin = dup(STDIN_FILENO);
    // int original_stdout = dup(STDOUT_FILENO);

    // if (original_stdin < 0 || original_stdout < 0)
    // {
    //    error_message(1, "dup error");
    //     return;
    // }
    // if (prepare_redirections(shell) < 0)
    // {
	// 	//error_message(1, "redir error");
	//     return;
    // }
    builtins(shell);
    // dup2(original_stdin, STDIN_FILENO);
    // dup2(original_stdout, STDOUT_FILENO);
    // close(original_stdin);
    // close(original_stdout);
}


static int is_directory(const char *path) {
    DIR *dir = opendir(path);

    if (dir) {
        closedir(dir);
        return 1;
    }
    return 0;
}


void execute_command(t_shell *shell)
 {
    char *pathname = NULL;

  	// if (!(shell->command->name))
    // {
    //     single_redir_file(shell -> command);
    //     return;
    // }
    if (is_builtin(shell->command->name))
	{
		//printf("barev\n");
        handle_builtin(shell);
        return;
    }
    // if (access(shell->command->name, X_OK | F_OK) == 0) {
	// 	  if (is_directory(shell->command->name)) {
    //         simple_error(126, shell->command->name, "is a directory");
    //         return;
    //     }
    //     pathname = ft_strdup(shell->command->name);
    // }
	// //if (check_non_directory())
    // if (pathname) {
    //     execute_execve(shell, &pathname);
    // } else {
    //     pathname = find_path(shell, shell->command->name);
    //     if (!pathname ) {
    //         simple_error(127, shell->command->name, "command not found");
    //         return;
    //     }
    //     execute_execve(shell, &pathname);
    // }
}

int	is_builtin(char *name)
{
	if (!ft_strcmp(name, "echo"))
		return (1);
	else if (!ft_strcmp(name , "pwd"))
		return (1);
	else if (!ft_strcmp(name , "cd"))
		return (1);
	else if (!ft_strcmp(name , "unset"))
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
