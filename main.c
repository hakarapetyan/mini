/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 19:32:14 by ashahbaz          #+#    #+#             */
/*   Updated: 2024/12/07 19:26:25 by ashahbaz         ###   ########.fr       */
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
static void execute_piped_commands(t_shell *shell)
{
    t_commands *cmd = shell->command;
    int pipefd[2];
    int prev_fd = STDIN_FILENO;

    while (cmd)
    {
        if (cmd->next)
        {
            if (pipe(pipefd) == -1)
                perror("pipe error");
        }

        // pid_t pid = fork();
        // if (pid == -1)
        // {
        //     perror("fork error");
        //     exit(EXIT_FAILURE);
        // }

        // if (pid == 0) // Child process
        // {
        //     // Redirect input
            if (prev_fd != STDIN_FILENO)
            {
                dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
            }

            // Redirect output
            if (cmd->next)
            {
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[1]);
                close(pipefd[0]);
            }

         execute(shell, cmd); // Your existing function to exec the command
          //  exit(EXIT_SUCCESS);
     //   }
        // else // Parent process
        // {
        //     waitpid(pid, NULL, 0); // Wait for the child process
        //     if (prev_fd != STDIN_FILENO)
        //         close(prev_fd);
        //     if (cmd->next)
        //         close(pipefd[1]);

            prev_fd = pipefd[0]; // Pass read end for next command
        // }

        cmd = cmd->next; // Move to the next command
    }
}

static int create_pipes(t_shell *shell)
{
	int	pipe_index;
	int	i;
	int	(*fd)[2];

	pipe_index = 0;
	i = 0;
	while (pipe_index < shell -> pipe_count)
	{

	}
}
static int	execution(t_shell *shell)
{
	shell -> pid = malloc(sizeof(int) * ((shell -> pipe_count) + 1));
	if(!(shell -> pid))
		//freeee
	create_pipes(shell);
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
		shell.input = readline("\033[1;37m.minishell \033[0m");
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
					execute_piped_commands(&shell); // Handles piped commands
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
