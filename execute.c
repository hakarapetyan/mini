/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:43:43 by ashahbaz          #+#    #+#             */
/*   Updated: 2024/12/15 13:00:06 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./include/minishell.h"


static void run_execve(t_shell *shell, char **pathname, t_commands *cmd)
{
	// int i = 0;
	// while (cmd -> args[i])
	// {
	// 	printf("%s\n",cmd -> args[i]);
	// 	i++;
	// }
	// printf("\n");
	// if (cmd -> error)
	// 	error_message(1, cmd -> error);
	//check this darling
	if (execve(*pathname, cmd->args,list_to_arr(shell -> env)) == -1)
	simple_error(127, cmd->name, "command not found");
	clean_shell_exit(shell, get_status());
}



int execute(t_shell *shell, t_commands *command)
{
    // pid_t pid;
	// int status;
	int i = 0;

	shell -> pid[i] = fork();
	if (shell -> pid[i] == 0)
	{
		printf("%d\n",shell -> pipe_index);
		if (shell -> pipe_index == 0)
		{
			printf("jhsdf\n");
			close(shell -> fd[0][0]);
			dup2(shell -> fd[0][1],1);
			close(shell -> fd[0][1]);
			execute_command(shell, command);
			exit(1);
		}
		else
		{
			printf("hello\n");
			close(shell -> fd[0][1]);
			dup2(shell -> fd[0][0], 0);
			close(shell -> fd[0][0]);
			execute_command(shell, command);
			exit(1);
		}
		i++;
		printf("isssss\n");
	}
		// pid = fork();
		// if (pid == 0)
		// {
		// 	// increment_shlvl(shell);
		// 	execute_command(shell, command);
		// }
		// else if (pid > 0)
		// {
		// 	waitpid(pid, &status, 0);
		// 	if (WIFEXITED(status))
		// 		set_status(WEXITSTATUS(status));
		// }
	return(0);
}


void handle_builtin(t_shell *shell, t_commands * command)
{
    builtins(shell, command);
    dup2(command -> stdin_original, STDIN_FILENO);
    dup2(command -> stdout_original, STDOUT_FILENO);
}


static int is_directory(char *path) {
    DIR *dir = opendir(path);
	if (path && ((path[0] == '.'&&  path[1] == '/') || path[ft_strlen(path) - 1] == '/' || path[0] == '/'))
	{
		if (dir) {
			closedir(dir);
			return 1;
		}
	}
    return 0;
}


int execute_command(t_shell *shell, t_commands *command)
 {
    char *pathname = NULL;

    if (is_builtin(command -> name))
	{
        handle_builtin(shell, command);
		return (0);
        // clean_shell_exit(shell, get_status());
    }
	if (access(command -> name, X_OK | F_OK) == 0)
	{
		if (is_directory(command -> name))
		{
			simple_error(126, command -> name, "is a directory");
			clean_shell_exit(shell, get_status());
		}
			pathname = ft_strdup(command -> name);
			//printf("%s\n",pathname);
	}
	if (command -> name[0] == '/' || (command -> name[0] == '.' && command -> name[1] == '/') )
	{
		if (access(command -> name, F_OK) != 0)
		{
			simple_error(127, command -> name, "No such file or directory");
			clean_shell_exit(shell, get_status());
		}
			pathname = ft_strdup(command -> name);
	}
		if (pathname)
			run_execve(shell, &pathname, command);
	else {
        pathname = find_path(shell, command -> name);
        if (!pathname ) {
			//error_message(127, command -> name);
            simple_error(127, command -> name, "command not found");
            clean_shell_exit(shell, get_status());
        }
        run_execve(shell, &pathname, command);
    }
	free(pathname);
	pathname = NULL;
	return (0);
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
