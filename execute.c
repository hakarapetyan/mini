/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakarape <hakarape@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:43:43 by ashahbaz          #+#    #+#             */
/*   Updated: 2024/12/07 22:49:48 by hakarape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./include/minishell.h"


static void run_execve(t_shell *shell, char **pathname)
{
	if (execve(*pathname, shell->command->args,list_to_arr(shell -> env)) == -1)
	{
		simple_error(127, shell->command->name, "command not found");
		clean_shell_exit(shell, get_status());
	}
}

static void handle_builtin(t_shell *shell)
{
    builtins(shell);
    dup2(shell -> command -> stdin_original, STDIN_FILENO);
    dup2(shell -> command -> stdout_original, STDOUT_FILENO);
}
int execute(t_shell *shell)
{
    pid_t pid;
	int status;

	if (is_builtin(shell->command->name))
		{
			handle_builtin(shell);
			return (0);
		// clean_shell_exit(shell, get_status());
		}
	else
	{
		signals(NINTERACTIVE);
		pid = fork();
		if (pid == 0)
			execute_command(shell);
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
	}
	return(0);
}





static int is_directory(char *path) {
    DIR *dir = opendir(path);
	if (path && ((path[0] == '.'&&  path[1] == '/') || path[ft_strlen(path) - 1] == '/'))
	{
		if (dir) {
			closedir(dir);
			return 1;
		}
	}
    return 0;
}


int execute_command(t_shell *shell)
 {
    char *pathname = NULL;

    
	if (access(shell->command->name, X_OK | F_OK) == 0)
	{
		if (is_directory(shell->command->name)) 
		{
			simple_error(126, shell->command->name, "is a directory");
			clean_shell_exit(shell, get_status());
		}
			pathname = ft_strdup(shell -> command -> name);
	}
	if (shell->command->name[0] == '/' || (shell->command->name[0] == '.' && shell->command->name[1] == '/') )
	{
		if (access(shell->command->name, F_OK) != 0)
		{
			simple_error(127, shell->command->name, "No such file or directory");
			clean_shell_exit(shell, get_status());
		}
			pathname = ft_strdup(shell -> command -> name);
	}
		if (pathname ) 
			run_execve(shell, &pathname);
	else {
        pathname = find_path(shell, shell->command->name);
        if (!pathname ) {
            simple_error(127, shell->command->name, "command not found");
            clean_shell_exit(shell, 127);
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
