/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 17:54:50 by ashahbaz          #+#    #+#             */
/*   Updated: 2024/12/14 16:13:49 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"



void	free_env(env_list *env)
{
	env_list	*tmp;

	if (env)
	{
		tmp = env;
		while (tmp)
		{
			tmp = tmp -> next;
			if (env -> value)
				free(env -> value);
			if (env -> key)
				free(env -> key);
			free(env);
			env = NULL;
			env = tmp;
		}
		free(env);
		env = NULL;
	}
}

void	free_tokens(t_token *token)
{
	t_token	*tmp;

	if (token)
	{
		tmp = token;
		while (tmp)
		{
			tmp = tmp -> next;
			if (token -> value)
				free(token -> value);
			if (token -> var_value)
				free(token -> var_value);
			free(token);
			token = tmp;
		}
		free(token);
		token = NULL;
	}
}

void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		args[i] = NULL;
		i++;
	}
	free(args);
}

void	free_commands(t_commands *command)
{
	t_commands *tmp;

	if (command)
	{
		tmp = command;
		while (tmp)
		{
			tmp = tmp -> next;
			if (command -> name)
				free(command -> name);
			if (command -> args)
				free_args(command -> args);
			if (command -> r_in)
				free(command -> r_in);
			if (command -> r_out)
				free(command -> r_out);
			if (command -> r_heredoc)
				free(command -> r_heredoc);
			if (command -> error)
				free(command -> error);
			command -> arg_count = 0;
			command -> args = NULL;
			free(command);
			command = tmp;
		}
		free (command);
		command = NULL;
	}
}

void	free_shell(t_shell *shell)
{
	free(shell -> input);
	shell -> input = NULL;
	free_tokens(shell -> token);
	free_commands(shell -> command);
	shell -> token_count = 0;
	shell -> command_count = 0;
	shell -> pipe_count = 0;
	shell -> pipe_index = 0;
	shell -> token = NULL;
	shell -> command = NULL;
}


void	free_str(char	*str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
}

void	free_arr(char **arr)
{
	if (*arr)
	{
		free(*arr);
		*arr = NULL;
	}
	arr = NULL;
}


void	clean_shell_exit(t_shell *shell, int status)
{
	free_env(shell -> env);
	shell -> env = NULL;
	free_env(shell -> exp);
	shell -> exp = NULL;
	free_shell(shell);
	exit(status);
}
