/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakarape <hakarape@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 19:32:14 by ashahbaz          #+#    #+#             */
/*   Updated: 2024/12/17 16:48:20 by hakarape         ###   ########.fr       */
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
		return (set_status(WTERMSIG(*status) + 128));
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
	if (cmd -> help == 1 && cmd -> name == NULL && shell -> command_count == 1)
		return (get_status());
	if (is_builtin(cmd -> name) && shell -> command_count == 1)
	{
		if (cmd -> help == 1)
			return (get_status());
		prepare_redirections(shell, cmd);
		handle_builtin(shell, cmd);
		return (get_status());
	}
	shell -> pid = malloc(sizeof(int) * (shell -> pipe_count + 1));
		//if (!shell -> pid) freee
	if (shell -> command_count > 1)
		create_pipes(shell);
	while (shell -> pipe_index <= shell -> pipe_count)
	{
		//signals(NINTERACTIVE);
		shell -> pid[i] = fork();
		if (shell -> pid[i] == 0)
		{
			if (cmd -> help == 1)
				clean_shell_exit(shell, get_status());
			if (shell -> command_count == 1)
			{
				prepare_redirections(shell, cmd);
				execute_command(shell, cmd);
				exit(get_status());
			}

			dups(shell);
			prepare_redirections(shell, cmd);
			execute_command(shell, cmd);
			exit(get_status());
		}
		dup2(cmd -> stdin_original, STDIN_FILENO);
		dup2(cmd -> stdout_original, STDOUT_FILENO);
		i++;
		shell -> pipe_index++;
		cmd = cmd -> next;
	}
	if (shell -> command_count > 1)
		close_pipes(shell);
	int k = 0;
	int st;
	while (k < shell->command_count)
	{
		wait_and_status(shell->pid[k], &st);
		k++;
	}
	return (get_status());
}


int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	(void)env;
	init_shell(&shell);
	//rl_catch_signals = 0;
	get_environment(&shell, env);
	chang_shlvl_in_env(&shell);
	chang_shlvl_in_exp(&shell);
	while (1)
	{
		//signals(INTERACTIVE);
		shell.input = readline("\033[1;35m.minishell \033[0m");
		if (!shell.input)
			clean_shell_exit(&shell,get_status());
		if (shell.input[0] != '\0')
			add_history(shell.input);
		lexical_analyzer(&shell);
		if (check_redir_errors(&shell) >= 0)
		{

			//print_tokens(&shell);
			create_commands(&shell);
			execution(&shell);
			//free_tokens(shell.token);
			//print_commands(&shell);
		}
		free_shell(&shell);
		//system("leaks minishell");
	}
	free_env(shell.env);
	shell.env = NULL;
	free_env(shell.exp);
	shell.exp = NULL;
	free_shell(&shell);
	system("leaks minishell");
	return (0);
}
