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
	t_token	*tkn;

	tkn = get_last_token(shell);
	if (tkn && (*flag) == 0)
	{
		(*flag)++;
		value = tkn ->value;
		new_value = ft_strjoin(value, " ");
		printf("val=%s|\n",new_value);
		if (new_value) {
			//free(value);
			//free((*shell) -> token -> value);
			tkn -> value = new_value;
		}
	}
	while (is_space(**current))
	(*current)++;
	printf("cr[%s]\n",*current);
}

void	handle_special_chars(t_shell *shell, char *current)
{
	t_lexer_state	state;
	//int				flag;

	//flag = 0;
	while (*current)
	{// printf("from[%s]\n",current);
		state = DEFAULT;
		state = set_state(*current, state);
	//	flag = 0;
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
			add_token(shell, SPACE, state, extract_whitespace(&current));
	}
}

char *extract_whitespace(char **current)
{
	char	*space;

	space = NULL;
	if (is_space(**current))
	{
		while (is_space(**current))
		{
			(*current)++;
		}
		space = ft_strdup(" ");
	}
	return (space);
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


static char *extract_var(char *str, t_shell *shell)
{
	char	*tmp;
	//int		i;

	//i = 0;
	tmp = NULL;
	if (!shell -> env)
		return (NULL);
	tmp = var_without_quotes(shell, &str);
	return (tmp);
}

static int	space_as_delim_strlen(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '$')
		i++;
	while(str[i] && (ft_isalnum(str[i])) )
	{
		i++;
	}
	return (i);
}
char	*extract_env_var(char **current, t_shell *shell)
{
	char	*var;
	//char	*res;
///	int	i;

//	i = 0;
	var = NULL;
	//res = NULL;
	var = extract_var(*current,shell);
	(*current) += space_as_delim_strlen(*current);
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
