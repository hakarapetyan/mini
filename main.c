/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 19:32:14 by ashahbaz          #+#    #+#             */
/*   Updated: 2024/11/10 17:41:15 by ashahbaz         ###   ########.fr       */
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

void	print_env(t_shell *shell)
{
	env_list	*current;

	current = shell->env;
	while (current)
	{
		printf("%s%s\n", current->key, current->value);
		current = current->next;
	}
}

void	print_exp(t_shell *shell)
{
	env_list	*current;

	current = shell->exp;
	while (current)
	{
		printf("declare -x %s\"%s\"\n", current->key, current->value);
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
char	**find_path_from_env(t_shell *shell)
{
	char		**path;
	char	*key;

	key = NULL;
	path = NULL;

	if (!(shell -> env))
		return (NULL);
	key = is_key(shell -> env, "PATH");
	if (!key)
		return (NULL);
	path = ft_split(key, ':');
	return (path);
}

static char	*find_path(t_shell *shell, char	*command_name)
{
	char	**path;
	char	*tmp;
	char	*tmp2;
	int		i;

	i = 0;
	path = find_path_from_env(shell);
	if (!path)
		return (NULL);
	while (path[i])
	{
		tmp = another_strjoin(path[i], "/");
		tmp2 = ft_strjoin(tmp,command_name);
		if (access(tmp2,X_OK) == 0)
		{
			free_arr(path);
			return (tmp2);
		}
		i++;
		free_arr(&tmp2);
	}
	return (NULL);
}

static void execute_command(t_shell *shell)
{
    pid_t pid;
    char *pathname;

    pathname = find_path(shell, get_last_command(shell)->name);
    if (!pathname) {
        fprintf(stderr, "zsh: command not found: %s\n", get_last_command(shell)->name);
        return;
    }
    pid = fork();
    if (pid == 0)
    {
        if (shell->command->r_in)
        {
            shell->command->fd_in = open(shell->command->r_in, O_RDONLY);
            if (shell->command->fd_in < 0) {
                perror("r_in failed to open");
                free(pathname);
                exit(EXIT_FAILURE);
            }
            if (dup2(shell->command->fd_in, STDIN_FILENO) < 0) {
                perror("dup2 failed for r_in");
                close(shell->command->fd_in);
                free(pathname);
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
                free(pathname);
                exit(EXIT_FAILURE);
            }
            close(shell->command->fd_out);
        }
        if (execve(pathname, shell->command->args, NULL) == -1)
        {
            perror("execve failed");
            free(pathname);
            exit(EXIT_FAILURE);
        }
    }
    else if (pid > 0)
        wait(NULL);
    else
        perror("fork failed");
    free(pathname);
}



//check get last command may cause seg


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
		//execute_echo(&shell);
		//print_tokens(&shell);
		//print_commands(&shell);
		//if (shell.command)
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
