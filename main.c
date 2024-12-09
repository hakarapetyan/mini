/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 19:32:14 by ashahbaz          #+#    #+#             */
/*   Updated: 2024/12/09 20:47:41 by ashahbaz         ###   ########.fr       */
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

	fd = malloc(sizeof(int[2]) * (shell -> pipe_count));
	if (!fd)
		error(ALLOCATION_ERR, shell);
	i = 0;
	while (i < shell -> pipe_count)
	{
		if (pipe(fd[i]) == -1)
		{
			while (i > 0)
			{
				//i--;
				i--;
				close(fd[i][0]);//read data from
				close(fd[i][1]);//write data to
			}
			free(fd);
			return (-1);
		}
		// printf("the 0 %d\n", fd[i][0]);
		// printf("the 1 %d\n", fd[i][1]);
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
static int	execution(t_shell *shell)
{
	t_commands *cmd;

	cmd = shell -> command;
	shell -> pid = malloc(sizeof(int) * (shell -> pipe_count + 1));
		//if (!shell -> pid) freee
	create_pipes(shell);
	while (shell -> pipe_index <= shell -> pipe_count)
	{
		execute(shell, cmd);
		cmd = cmd -> next;
		shell -> pipe_index++;
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
	//rl_catch_signals = 0;
	while (1)
	{
		// rl_replace_line("", 0);
		// rl_on_new_line();
		shell.input = readline("\033[1;35m.minishell \033[0m");
		//	system("leaks minishell");
		if (!shell.input)
			break;
		// error(READLINE_ERR, &shell);
		if (shell.input[0] != '\0')
			add_history(shell.input);
		get_environment(&shell, env);
		lexical_analyzer(&shell);
		if (check_redir_errors(&shell) >= 0)
		{
				//print_tokens(&shell);
			if (create_commands(&shell) >= 0)
			{
				//free_tokens(shell.token);
				//print_commands(&shell);
				//create_pipes(&shell);
				 prepare_redirections(&shell);
			//	if (contains_pipes(shell.command)) // Implement this function
					execution(&shell); // Handles piped commands
              //  else
               //     execute(&shell); // Handles regular commands

				//execute(&shell);
				dup2(shell.command -> stdin_original, STDIN_FILENO);
   				dup2(shell.command -> stdout_original, STDOUT_FILENO);
			}
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
