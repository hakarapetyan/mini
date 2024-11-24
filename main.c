/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakarape <hakarape@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 19:32:14 by ashahbaz          #+#    #+#             */
/*   Updated: 2024/11/24 16:14:12 by hakarape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	print_commands(t_shell *shell)
{
	t_commands	*current;
	int			i;

	i = 0;
	current = shell->command;
	while (current)
	{
		printf("Command: %s, R_in: %s , R_out: %s\n", current->name, current -> r_in, current -> r_out);
		if (current -> args)
		{
			i = 0;
			while (current -> args[i])
			{
				printf("index: %d , Args:%s \n", i, current -> args[i]);
				i++;
			}
		}
		current = current->next;
	}
}

void	print_tokens(t_shell *shell)
{
	t_token	*current;

	current = shell->token;
	while (current)
	{
		printf("Token: %s | Type: %d | State: | %d Variable: | %s\n",
			current->value, current->type, current->state, current->var_value);
		current = current->next;
	}
}
void	redir_check(t_token_type type,t_shell *shell)
{
	if (type == R_IN)
		error("syntax error near unexpected token `<'", shell);
	else if (type == R_OUT)
		error("syntax error near unexpected token `>'", shell);
	else if (type == R_APPEND)
		error("syntax error near unexpected token `>>'", shell);
	else if (type == R_HEREDOC)
		error("syntax error near unexpected token `<<'", shell);
}
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


/*void	execute_command(char *command,char **args,t_shell *shell)
{
	pid_t	pid;
	const char *pathname;

	pid = fork();
	pathname = NULL;
	(void)command;
	if (pid < 0)
		error("processss",shell);
	if (pid == 0)
	{
		pathname = "/bin/ls";
		if (execve(pathname, args, NULL) == -1)
			error("processss",shell);
	}
	else
		wait(NULL);
}*/

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	init_shell(&shell);
	get_environment(&shell, env);
	while (1)
	{
		shell.input = readline("\033[1;37m.minishell \033[0m");
	//	system("leaks minishell");
		if (!shell.input)
			error(READLINE_ERR, &shell);
		if (shell.input[0] != '\0')
			add_history(shell.input);
		//print_env(&shell);
		lexical_analyzer(&shell);
		//check_redir_errors(&shell);
		create_commands(&shell);
		//print_tokens(&shell);
		//print_commands(&shell);
		//execute_command(shell.command);
		// execute_cd(&shell);
		// execute_echo(&shell);
		// execute_exit(&shell);
		// execute_unset(&shell);
		// execute_env(&shell);
		// execute_export(&shell);
		builtins(&shell);
	 //	execute_command((shell.command) -> name, (shell.command )-> args,&shell);
		free_shell(&shell);
	// 	//system("leaks minishell");
	}
	//free_env(shell.env);
	//shell.env = NULL;
	free_shell(&shell);
	//system("leaks minishell");
	return (0);
}
