#include "./include/minishell.h"

static void	get_redir_helper(t_token **token,  t_shell *shell, char **type)
{
	if (*type)
		free(*type);
	if (*token && (*token) -> next)
		*type = ft_strdup((*token) -> next -> value);
	if (!(*type))
		error(ALLOCATION_ERR, shell);

//	open_the_file(shell, (*type));
}

void	get_redir(t_token **token,t_commands **tmp,  t_shell *shell)
{
	if ((*token) -> type == R_IN)
		get_redir_helper(token, shell, &((*tmp) -> r_in));
	else if ((*token) -> type == R_OUT)
		get_redir_helper(token, shell, &((*tmp) -> r_out));
	else if ((*token) -> type == R_APPEND)
	{
		get_redir_helper(token, shell, &((*tmp) -> r_out));
		(*tmp) -> is_append = 1;
	}
	else if ((*token) -> type == R_HEREDOC)
	{
		get_redir_helper(token, shell, &((*tmp) -> r_heredoc));
	}
	(*token) = (*token)->next ? (*token)->next->next : NULL;
}