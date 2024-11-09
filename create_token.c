#include "./include/minishell.h"

t_token	*create_token(t_token_type type, t_lexer_state state, char *value)
{
	t_token	*token;

	if (!value)
		return (NULL);
	token = malloc(sizeof(t_token));
	if (!token) // allocation failed;
		return (NULL);
	token->type = type;
	token->value = value;
	token->space = 0;
	token->var_value = NULL;
	token->state = state;
	if (!token)
	{
		free_tokens(token);
		return (NULL); // alocation failed
	}
	token->next = NULL;
	return (token);
}

void	add_token(t_shell *shell, t_token_type type, t_lexer_state state,
		char *value)
{
	t_token	*current;

	if (!value || !*value)
		return ;
	if (!((shell)->token))
	{
		(shell)->token = create_token(type, state, value);
		if (!((shell)->token))
			error(ALLOCATION_ERR, shell);
		(shell)->token_count++;
	//	expand_var(shell);
	}
	else
	{
		current = (shell)->token;
		while (current->next)
			current = current->next;
		current->next = create_token(type, state, value);
		if (!(current->next))
			error(ALLOCATION_ERR, shell);
		(shell)->token_count++;
		//expand_var(shell);
	}
}
