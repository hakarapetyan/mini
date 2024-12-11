/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakarape <hakarape@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 19:32:14 by ashahbaz          #+#    #+#             */
/*   Updated: 2024/12/11 20:51:30 by hakarape         ###   ########.fr       */
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

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	(void)env;
	//init_shell(&shell);
	rl_catch_signals = 0;
		get_environment(&shell, env);
		chang_shlvl(&shell);
	while (1)
	{
		// rl_replace_line("", 0);
		// rl_on_new_line();
		signals(INTERACTIVE);
		shell.input = readline("\033[1;35m.minishell \033[0m");
		//	system("leaks minishell");
		if (!shell.input)
			break;//free anel
		// error(READLINE_ERR, &shell);
		if (shell.input[0] != '\0')
			add_history(shell.input);
		lexical_analyzer(&shell);
		if (check_redir_errors(&shell) >= 0)
		{
				//print_tokens(&shell);
			if (create_commands(&shell) >= 0)
			{
				//free_tokens(shell.token);
				//print_commands(&shell);
				if (prepare_redirections(&shell) >= 0)
				{
					execute(&shell);
					
				}
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
	// printf("%lld\n",ft_atoi("999"));
	// printf("%lld\n",ft_atoi("1"));
	// printf("%lld\n",ft_atoi("0"));
	// printf("%lld\n",ft_atoi("9223372036854775809"));
	return (0);
}
