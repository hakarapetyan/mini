

#include "./include/minishell.h"


static void	wait_and_status(pid_t pid, int *status)
{
	waitpid(pid, status, 0);
	if (WIFSIGNALED(*status))
		return (set_status(WTERMSIG(*status) + 128));
	set_status(WEXITSTATUS(*status));
}

static int only_one_builtin(t_shell *shell,t_commands *cmd)
{
    if (cmd -> help == 1 && cmd -> name == NULL && shell -> command_count == 1)
		return (get_status());
	if (cmd -> name && is_builtin(cmd -> name) && shell -> command_count == 1)
	{
		if (cmd -> help == 1)
			return (get_status());
		prepare_redirections(shell, cmd);
		handle_builtin(shell, cmd);
		return (get_status());
	}
    return (-1);
}


static int create_processes(t_shell *shell,t_commands *cmd)
{
    int i = 0;

    while (shell -> pipe_index <= shell -> pipe_count)
	{
		signals(NINTERACTIVE);
		shell -> pid[i] = fork();
        if (shell -> pid[i] == -1)
        {
            set_status(EXIT_FAILURE);
            return(-1);
        }
		if (shell -> pid[i] == 0)
		{
			if (cmd -> help == 1)
				clean_shell_exit(shell, get_status());
            if (shell -> command_count > 1)
		    	dups(shell);
			prepare_redirections(shell, cmd);
			execute_command(shell, cmd);
			exit(get_status());
		}
		i++;
		shell -> pipe_index++;
		cmd = cmd -> next;
	}
    return (get_status());
}

int	execution(t_shell *shell)
{
	t_commands *cmd;
	int k = 0;
	int st;

	cmd = shell -> command;
	if (only_one_builtin(shell,cmd) != -1)
        return (get_status());
	shell -> pid = malloc(sizeof(int) * (shell -> pipe_count + 1));
	if (!shell -> pid)
        clean_shell_exit(shell,EXIT_FAILURE);  
	if (shell -> command_count > 1)
		create_pipes(shell);
    create_processes(shell, cmd);//dziiii 
	if (shell -> command_count > 1)
		close_pipes(shell);
	while (k < shell->command_count)
	{
		wait_and_status(shell->pid[k], &st);
		k++;
	}
	return (get_status());
}