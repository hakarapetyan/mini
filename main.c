/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 19:32:14 by ashahbaz          #+#    #+#             */
/*   Updated: 2024/11/10 18:07:25 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	check_redir_errors(t_shell *shell)
{
	t_token	*tkn;

	tkn = shell -> token;
	if (tkn -> type == PIPE)
			error("syntax error near unexpected token `|'", shell);
	while (tkn)
	{
		// if (is_redirection(tkn -> type) && !(tkn -> next))
		// 	error("syntax error near unexpected token `newline'", shell);
		if (is_redirection(tkn -> type) && (tkn -> next && tkn -> next -> type == PIPE))
			error("syntax error near unexpected token `|'", shell);
		if (is_redirection(tkn -> type) && (tkn -> next && is_redirection(tkn -> next -> type)))
			redir_check(tkn -> next -> type ,shell);
		if (tkn -> type == PIPE && !(tkn -> next))
			error("syntax error near unexpected token `|'", shell);
		if (tkn -> type == PIPE && tkn -> next -> type == PIPE)
			error("syntax error near unexpected token `||'", shell);

		tkn = tkn -> next;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	init_shell(&shell);
	while (1)
	{
		shell.input = readline("\033[1;37m.minishell \033[0m");
		//	system("leaks minishell");
		if (!shell.input)
			break;
		// error(READLINE_ERR, &shell);
		if (shell.input[0] != '\0')
			add_history(shell.input);
		get_environment(&shell, env);
		lexical_analyzer(&shell);
		//check_redir_errors(&shell);
		create_commands(&shell);
		//print_tokens(&shell);
		//print_commands(&shell);
		execute_command(&shell);
		free_shell(&shell);
		//system("leaks minishell");
	}
	// free_env(shell.env);
	// shell.env = NULL;
	free_shell(&shell);
	//system("leaks minishell");
	return (0);
}
