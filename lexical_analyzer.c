#include "./include/minishell.h"

void lexical_analyzer(t_shell *shell)
{
	int	status;

	status = tokenization(shell);
	if (status == -2)
		error(QUOTE_ERR, shell);
}

void add_space(t_shell *shell, char **current, int *flag)
{
    char	*value;
	char	*new_value;

	if ((shell) -> token && (*flag) == 0)
	{
		(*flag)++;
		value = (shell) -> token ->value;
		new_value = ft_strjoin(value, " ");
		if (new_value) {
			//free(value);
			//free((*shell) -> token -> value);
			(shell) -> token -> value = new_value;
		}
	}
	(*current)++;
}

void	handle_special_chars(t_shell *shell, char *current)
{
	t_lexer_state	state;
	int				flag;

	flag = 0;
	while (*current)
	{
		state = DEFAULT;
		state = set_state(*current, state);
		if (*current == '|')
			add_token(shell, PIPE, state, extract_separator(&(current)));
		else if (*current == '<' && (*(current + 1)) == '<')
			add_token(shell, R_HEREDOC, state, extract_separator(&(current)));
		else if (*current == '>' && (*(current + 1)) == '>')
			add_token(shell, R_APPEND, state, extract_separator(&(current)));
		else if (*current == '<')
			add_token(shell, R_IN, state, extract_separator(&(current)));
		else if (*current == '>')
			add_token(shell, R_OUT, state, extract_separator(&(current)));
		else if (*current == '$')
			add_token(shell, ENV_VAR, state, extract_env_var(&(current),shell));
		else if (!(is_separator(*current)) && !(is_space(*current)))
			add_token(shell, WORD, state, extract_word(&(current),shell));
		else if (is_space(*current))
			add_space(shell, &current, &flag);
	}
}


int	tokenization(t_shell *shell)
{
	char			*current;

	current = shell -> input;
	if (!are_quotes_even(shell -> input))
		return (-2);
	handle_special_chars(shell, current);
	//expand_heredoc(shell);
	return (0);
}

char	*extract_env_var(char **current, t_shell *shell)
{
	char	*var;
	char	*res;
	int	i;

	i = 0;
	var = NULL;
	res = NULL;
	if ((*current)[i] == '$' && (!((*current)[i + 1]) || is_quote((*current)[i + 1])))
	{
		(*current)++;
		return (ft_strdup("$"));
	}
	i++;
	if (ft_isalnum((*current)[i]) == 1 || (*current)[i] == '_')
	{
		while ((*current)[i] && (ft_isalnum((*current)[i]) || (*current)[i] == '_'))
			i++;
		var = ft_substr(*current, 0, i);
	}
	else
		return (NULL);
	while(i)
	{
		(*current)++;
		i--;
	}
	if(ft_search(var,shell))
	{
		if (ft_search(var, shell) == 2)
		{
			free_arr(&var);
			return(ft_strdup(""));
		}
		else if (ft_search(var, shell) == 1)
		{
			res = ft_substr(var, 1, ft_strlen(var) - 1);
			free_arr(&var);
			return(res);
		}
	}
	return (var);
}


char	*extract_separator(char **current)
{
	char	*var;
	int	i;

	i = 1;
	if(**current == '<' && (*(*current + 1) == '<'))
		i++;
	else if(**current == '>' && (*(*current + 1) == '>'))
		i++;
	var = ft_substr(*current, 0, i);
	*current += i;
	return (var);
}
