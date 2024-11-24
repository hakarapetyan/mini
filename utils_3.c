/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:42:31 by ashahbaz          #+#    #+#             */
/*   Updated: 2024/11/24 16:42:36 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./include/minishell.h"

int	is_redirection(t_token_type type)
{
	if (type == R_IN|| type == R_OUT ||
			type == R_APPEND || type == R_HEREDOC)
		return	(1);
	return (0);
}


int	args_count(t_token **token)
{
	int	count;
	t_token	*tmp;

	count = 0;
	tmp = *token;
	while (tmp && (tmp -> type != PIPE))
	{
		if (is_redirection(tmp -> type) && tmp -> next && tmp -> next -> next)
		{
			tmp = tmp -> next -> next;
		}
		count++;
		if (tmp)
			tmp = tmp -> next;
	}
	return (count);
}
t_token *get_last_token(t_shell *shell)
{
	if (shell -> token)
	{
		t_token	*tkn;

		tkn = shell -> token;
		while (tkn -> next)
		{
			tkn = tkn -> next;
		}
		return (tkn);
 	}
	return (NULL);
}

t_commands *get_last_command(t_shell *shell)
{
	if (shell -> command)
	{
		t_commands	*cmd;
		cmd = shell -> command;
		while (cmd -> next)
		{
			cmd = cmd -> next;
		}
		return (cmd);
	}
	return (NULL);
}

t_token *get_the_token_i_want(t_shell *shell)
{
	if (shell -> token)
	{
		t_token	*tkn;

		tkn = shell -> token;
		while (tkn -> next -> next)
		{
			tkn = tkn -> next;
		}
		return (tkn);
 	}
	return (NULL);
}


