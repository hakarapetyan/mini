#include "./include/minishell.h"


static void execute_builtins(t_shell *shell)
{
	char	*cmd;

	cmd = shell -> command -> name;
	if (!ft_strcmp(cmd,"echo"))
		execute_echo(shell);
}
static void	prepare_redirections(t_shell *shell, char **pathname)
{
	if (shell->command->r_in)
	{
		shell->command->fd_in = open(shell->command->r_in, O_RDONLY);
		if (shell->command->fd_in < 0) {
			no_such_file_error(shell -> command -> r_in);
			free(*pathname);
			exit(EXIT_FAILURE);
		}
		if (dup2(shell->command->fd_in, STDIN_FILENO) < 0) {
			permission_error(shell -> command -> r_in);
			close(shell->command->fd_in);
			free(*pathname);
			exit(EXIT_FAILURE);
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
			no_such_file_error(shell -> command -> r_out);
			free(*pathname);
			exit(EXIT_FAILURE);
		}
		if (shell->command->fd_out >= 0)
		{
			if (dup2(shell->command->fd_out, STDOUT_FILENO) < 0)
			{
				permission_error(shell -> command -> r_out);
				close(shell->command->fd_out);
				free(*pathname);
				exit(EXIT_FAILURE);
			}
		}
			close(shell->command->fd_out);
	}
}
static void run_execve(t_shell *shell, char **pathname)
{
	if (execve(*pathname, shell->command->args, NULL) == -1)
	{
		perror("execve failed");
		free(*pathname);
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
        perror("fork failed");
    free(*pathname);
}
void static single_redir_file(t_shell *shell)
{
	if (shell->command->r_in)
	{
		shell->command->fd_in = open(shell->command->r_in, O_RDONLY);
		if (shell->command->fd_in < 0)
		{
			no_such_file_error(shell -> command -> r_in);
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
			no_such_file_error(shell -> command -> r_out);
		}
		close(shell->command->fd_out);
	}
}

void execute_command(t_shell *shell)
{
	if (!(shell -> command -> name))
	{
		single_redir_file(shell);
		return;
	}
	else
	{
		char *pathname;
		pathname = find_path(shell, get_last_command(shell)->name);
		if (!pathname) {
			//single_redir_file(shell);
			fprintf(stderr, "zsh: command not found: %s\n", get_last_command(shell)->name);
			return;
		}
			execute_execve(shell, &pathname);
	}
	// if(shell -> command_count == 1 && is_builtin(shell -> command -> name))
	// 	execute_builtins(shell);
	// else
	// {
	// 	printf("from execve\n");
//	}
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
