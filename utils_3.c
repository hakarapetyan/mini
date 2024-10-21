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
			tmp = tmp -> next -> next;
		count++;
		if (tmp)
			tmp = tmp -> next;
	}
	return (count);
}
t_token *get_last_token(t_shell *shell)
{
	t_token	*tkn;

	tkn = shell -> token;
	while (tkn -> next)
	{
		tkn = tkn -> next;
	}
	return (tkn);
}
