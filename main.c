/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 19:32:14 by ashahbaz          #+#    #+#             */
/*   Updated: 2024/12/11 18:24:12 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int status = 0;

static int	check_redir_errors(t_shell *shell)
{
	t_token	*tkn;

	tkn = shell -> token;
	if (!tkn)
		return (-1);
	if (tkn -> type == PIPE)
	{
		syntax_error(tkn -> value);
			return (-1);
	}
	while (tkn)
	 {
		if (is_redirection(tkn -> type) && ((tkn -> next && is_redirection(tkn -> next -> type)) ||
			 !(tkn -> next) || (tkn -> next && tkn -> next -> type == PIPE)))
		{
			if (tkn -> next)
			syntax_error(tkn -> next -> value);
			else if (!(tkn -> next))
				syntax_error("newline");
			return (-1);
		}
		if (tkn -> type == PIPE && ((tkn -> next && tkn -> next -> type == PIPE) ||
			 !(tkn -> next) || (tkn -> next && tkn -> next -> type == PIPE)))
		{
			if (tkn -> next)
			syntax_error(tkn -> next -> value);
			else if (!(tkn -> next))
				syntax_error("newline");
			return (-1);
		}
		 tkn = tkn -> next;
	}
	return (0);
}


static int create_pipes(t_shell *shell)
{
	int	i;
	int	(*fd)[2];

	i = 0;
	fd = malloc(sizeof(int[2]) * (shell -> pipe_count));
	if (!fd)
		error(ALLOCATION_ERR, shell);
	while (i < shell -> pipe_count)
	{
		if (pipe(fd[i]) == -1)
		{
			while (i > 0)
			{
				i--;
				close(fd[i][0]);
				close(fd[i][1]);
			}
			free(fd);
			return (-1);
		}
		i++;
	}
	shell -> fd = fd;
	return (0);
}


int close_pipes(t_shell *shell)
{
	int i;

	i = 0;
	while (i < shell -> pipe_count)
	{
		close(shell -> fd[i][0]);
		close(shell -> fd[i][1]);
		i++;
	}
	return (0);
}

static void	wait_and_status(pid_t pid, int *status)
{
	waitpid(pid, status, 0);
	if (WIFSIGNALED(*status))
	{
		*status = WTERMSIG(*status) + 128;
		if (*status == 131)
			write(1, "Quit: 3\n", 9);
		return (set_status(*status));
	}
	set_status(WEXITSTATUS(*status));
}

static void dups(t_shell *shell)
{
	if (shell->pipe_index == 0)
	{
		//printf("first\n");
		if (dup2(shell->fd[0][1], 1) == -1)
		{
			close_pipes(shell);
			printf("pipe dup failed\n");
			clean_shell_exit(shell, 1);
		}
	}
	else if (shell->pipe_index == shell->pipe_count)
	{
		//printf("last\n");
		if (dup2(shell->fd[shell->pipe_index - 1][0], 0) == -1)
		{
			close_pipes(shell);
			printf("pipe dup failed\n");
			clean_shell_exit(shell, 1);
		}
	}
	else
	{
		//printf("middle\n");
		if (dup2(shell->fd[shell->pipe_index - 1][0], 0) == -1)
		{
			close_pipes(shell);
			printf("pipe dup failed\n");
			clean_shell_exit(shell, 1);
		}
		if (dup2(shell->fd[shell->pipe_index][1], 1) == - 1)
		{
			close_pipes(shell);
			printf("pipe dup failed\n");
			clean_shell_exit(shell, 1);
		}
	}
	close_pipes(shell);
}
static int	execution(t_shell *shell)
{
	t_commands *cmd;
	int i = 0;

	cmd = shell -> command;
	//printf("%s\n",cmd -> name);
	if (is_builtin(cmd -> name) && shell -> command_count == 1)
	{
		prepare_redirections(shell, cmd);
		handle_builtin(shell, cmd);
		return (0);
	}
	shell -> pid = malloc(sizeof(int) * (shell -> pipe_count + 1));
		//if (!shell -> pid) freee
	create_pipes(shell);
	while (shell -> pipe_index <= shell -> pipe_count)
	{
		shell -> pid[i] = fork();
		if (shell -> pid[i] == 0)
		{
			if (shell -> command_count == 1)
			{
				execute_command(shell, cmd);
				exit(0);
			}
			dups(shell);
			prepare_redirections(shell, cmd);
			execute_command(shell, cmd);
			exit(0);
		}
		dup2(cmd -> stdin_original, STDIN_FILENO);
		dup2(cmd -> stdout_original, STDOUT_FILENO);
		i++;
		shell -> pipe_index++;
		cmd = cmd -> next;
	}
	close_pipes(shell);
	int k = 0;
	int st;
	while (k < shell->command_count)
	{
		wait_and_status(shell->pid[k], &st);
		k++;
	}
	return ( 0);
}


int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	init_shell(&shell);
	while (1)
	{
		shell.input = readline("\033[1;35m.minishell \033[0m");
		if (!shell.input)
			break;
		if (shell.input[0] != '\0')
			add_history(shell.input);
		get_environment(&shell, env);
		lexical_analyzer(&shell);
		if (check_redir_errors(&shell) >= 0)
		{
			//print_tokens(&shell);
			create_commands(&shell);
			//free_tokens(shell.token);
			//print_commands(&shell);
			// prepare_redirections(&shell);
			execution(&shell);
		}
		free_shell(&shell);
		//system("leaks minishell");
	}
	free_env(shell.env);
	shell.env = NULL;
	free_env(shell.exp);
	shell.exp = NULL;
	free_shell(&shell);
	//system("leaks minishell");
	return (0);
}
