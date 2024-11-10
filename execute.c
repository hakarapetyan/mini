#include "./include/minishell.h"


static void execute_builtins(t_shell *shell)
{
	char	*cmd;

	cmd = shell -> command -> name;
	if (!ft_strcmp(cmd,"echo"))
		execute_echo(shell);
}

static void execute_execve(t_shell *shell, char **pathname)
{
    pid_t pid;

    pid = fork();
    if (pid == 0)
    {
        if (shell->command->r_in)
        {
            shell->command->fd_in = open(shell->command->r_in, O_RDONLY);
            if (shell->command->fd_in < 0) {
                perror("r_in failed to open");
                free(*pathname);
                exit(EXIT_FAILURE);
            }
            if (dup2(shell->command->fd_in, STDIN_FILENO) < 0) {
                perror("dup2 failed for r_in");
                close(shell->command->fd_in);
                free(*pathname);
                exit(EXIT_FAILURE);
            }
            close(shell->command->fd_in);
        }
        if (shell->command->is_append)
            shell->command->fd_out = open(shell->command->r_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
        else if (shell->command->r_out)
            shell->command->fd_out = open(shell->command->r_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (shell->command->fd_out >= 0)
        {
            if (dup2(shell->command->fd_out, STDOUT_FILENO) < 0) {
                perror("dup2 failed for r_out");
                close(shell->command->fd_out);
                free(*pathname);
                exit(EXIT_FAILURE);
            }
            close(shell->command->fd_out);
        }
        if (execve(*pathname, shell->command->args, NULL) == -1)
        {
            perror("execve failed");
            free(*pathname);
            exit(EXIT_FAILURE);
        }
    }
    else if (pid > 0)
        wait(NULL);
    else
        perror("fork failed");
    free(*pathname);
}


void execute_command(t_shell *shell)
{
	char *pathname;

	pathname = find_path(shell, get_last_command(shell)->name);
    if (!pathname) {
        fprintf(stderr, "zsh: command not found: %s\n", get_last_command(shell)->name);
        return;
    }
	if(shell -> command_count == 1 && pathname)
		execute_builtins(shell);
	else
		execute_execve(shell, &pathname);
}
