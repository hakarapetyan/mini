#include "./include/minishell.h"

void	expand_var(t_shell *shell)
{
    t_token *current;
    char *key;

	if (!shell -> env)
		return ;
    current = shell->token;
    key = NULL;
    while (current)
    {
        if (current->type == ENV_VAR)
        {
			key = is_key(shell->env, current->value);
            if (key)
				current->var_value = ft_strdup(getenv(key));
        }
        current = current->next;
    }
}

int	is_word(char *str)
{
	while (*str)
	{
		if (is_separator(*str))
			return (0);
		str++;
	}
	return (1);
}

void	expand_heredoc(t_shell *shell)
{
	t_token	*current;

	current = shell -> token;
	while (current)
	{
		if (current -> type == R_HEREDOC)
		{
			current = current -> next;
			if (current -> next)
			{
				error(SYNTAX_ERR, shell);
				free_tokens(shell -> token);
			}
		}
		current = current -> next;
	}
}
