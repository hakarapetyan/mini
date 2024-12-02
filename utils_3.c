/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:42:31 by ashahbaz          #+#    #+#             */
/*   Updated: 2024/12/02 15:16:50 by ashahbaz         ###   ########.fr       */
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
		if (is_redirection(tmp -> type))
		{
			if (tmp -> next)
				tmp = tmp -> next;
			else
				break;
			if (tmp -> next)
				tmp = tmp -> next;
			else
				break;
		}
		else
		{
			count++;
			tmp = tmp -> next;
		}
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


void	token_count(t_shell *shell)
{
	t_token *tkn;
	int count;

	count = 0;
	tkn = shell -> token;
	if (!tkn)
	{
		shell -> token_count = count;
		return;
	}
	while (tkn)
	{
		count++;
		tkn = tkn -> next;
	}
	shell -> token_count = count;
}
