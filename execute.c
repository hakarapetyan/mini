/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:43:43 by ashahbaz          #+#    #+#             */
/*   Updated: 2024/12/07 17:39:14 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./include/minishell.h"


static void run_execve(t_shell *shell, char **pathname)
{
	if (execve(*pathname, shell->command->args,list_to_arr(shell -> env)) == -1)
	{
		//error_message(1, shell -> command -> name);
		simple_error(127, shell->command->name, "command not found");
		clean_shell_exit(shell, get_status());
	}
}

// static void increment_shlvl(t_shell *shell)
// {

// 	shell -> shlvl++;
// }
int execute(t_shell *shell, t_commands *command)
{
    pid_t pid;
	int status;

    pid = fork();
    if (pid == 0)
	{
		// increment_shlvl(shell);
		execute_command(shell, command);
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
	return(0);
}


static void handle_builtin(t_shell *shell)
{
    builtins(shell);
    dup2(shell -> command -> stdin_original, STDIN_FILENO);
    dup2(shell -> command -> stdout_original, STDOUT_FILENO);
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
        handle_builtin(shell);
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
			run_execve(shell, &pathname);
	else {
        pathname = find_path(shell, command -> name);
        if (!pathname ) {
			//error_message(127, command -> name);
            simple_error(127, command -> name, "command -> name not found");
            clean_shell_exit(shell, get_status());
        }
        run_execve(shell, &pathname);
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
