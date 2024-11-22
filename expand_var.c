#include "./include/minishell.h"

void	expand_var(t_shell *shell)
{
    t_token *current;
	//char	*tmp;
    char	*key;

	if (!shell -> env)
		return ;
    current = shell->token;
    key = NULL;
    while (current)
    {
        if (current->type == ENV_VAR)
        {
			//printf("{%s}\n",current -> value);
			key = is_key(shell->env, current->value);
            if (key)
			{
				current -> var_value = ft_strdup(getenv(key));
			//	current -> var_value = add_space_to_env_var(current -> value, tmp);
			}
        }
        current = current->next;
    }
}

char	*generate_spaces(int count)
{
	char	*s;
	int		i;

	i = 0;
	s = (char *)malloc((count + 1) * sizeof(char));
    if (!s) {
        return NULL;
    }
	while (count)
	{
		s[i] = ' ';
		i++;
	}
	return (s);
}

char	*add_space_to_env_var(char *str, char *tmp)
{
	int	i;
	int	count;
	char	*var;

	i = 0;
	count = 0;
	printf("str[%s]\n",str);
	while (str[i])
	{
		if (str[i] && str[i] == ' ')
			count++;
		i++;
	}
	printf("cnt%d\n",count);
	printf("tmp%s\n",generate_spaces(count));
	var = ft_strjoin(tmp, generate_spaces(count));
	return(var);
	if(!var)
		return (NULL);
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
				error(SYNTAX_ERR_MSG, shell);
				free_tokens(shell -> token);
			}
		}
		current = current -> next;
	}
}
