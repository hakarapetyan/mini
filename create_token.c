/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:43:52 by ashahbaz          #+#    #+#             */
/*   Updated: 2024/12/14 16:40:59 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./include/minishell.h"

static t_token	*create_token(t_shell *shell, t_token_type type, t_lexer_state state, char *value)
static t_token	*create_token(t_shell *shell, t_token_type type, t_lexer_state state, char *value)
{
	t_token	*token;

	if (!value)
		return (NULL);
	token = malloc(sizeof(t_token));
	if (!token)
	{
		error(ALLOCATION_ERR, shell);
		return (NULL); // alocation failed
	}
	if (!token)
	{
		error(ALLOCATION_ERR, shell);
		return (NULL); // alocation failed
	}
	token->type = type;
	token->value = value;
	token->space = 0;
	token->var_value = NULL;
	token->state = state;
	token->next = NULL;
	return (token);
}

void	add_token(t_shell *shell, t_token_type type, t_lexer_state state,
		char *value)
{
	t_token	*current;

	if (!value)
	if (!value)
		return ;
	if (!((shell)->token))
	{
		(shell)->token = create_token(shell, type, state, value);
		(shell)->token = create_token(shell, type, state, value);
		if (!((shell)->token))
			error(ALLOCATION_ERR, shell);
		//(shell)->token_count++;
		expand_var(shell);
		//(shell)->token_count++;
		expand_var(shell);
	}
	else
	{
		current = (shell)->token;
		while (current->next)
			current = current->next;
		current->next = create_token(shell, type, state, value);
		current->next = create_token(shell, type, state, value);
		if (!(current->next))
			error(ALLOCATION_ERR, shell);
		//shell)->token_count++;
		expand_var(shell);
		//shell)->token_count++;
		expand_var(shell);
	}
}
