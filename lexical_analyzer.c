#include "./include/minishell.h"

void lexical_analyzer(t_shell *shell)
{
	int	status;

	status = tokenization(shell);
	if (status == -2)
		error(QUOTE_ERR, shell);
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
			add_token(shell, ENV_VAR, state, extract_word(&(current),shell));
		else if (!(is_separator(*current)) && !(is_space(*current)))
			add_token(shell, WORD, state, extract_word(&(current),shell));
		else if (is_space(*current))
			add_token(shell, TK_SPACE, state, extract_whitespace(&current));
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

// static void	token_list_without_spaces(t_shell *shell)
// {
// 	t_token	*tkn = shell -> token;
// 	t_token	*previous = NULL;
// 	t_token	*tmp;

// 	while (tkn -> next)
// 	{
// 		if (tkn -> type == TK_SPACE)
// 		{
// 			tmp = tkn;
// 			tkn = tkn -> next;
// 			if (previous)
// 				previous -> next = tkn;
// 			free(tmp -> value);
// 			free(tmp);
// 		}
// 		if (tkn -> type != TK_SPACE && tkn -> next && tkn -> next -> type != TK_SPACE)
// 		{
// 			tkn -> value = ft_strjoin(tkn -> value, tkn -> next -> value);
// 			tmp = tkn -> next;

// 			tkn -> next = tmp -> next;
// 			free(tmp -> value);
// 			free(tmp);
// 		}
// 		else
// 		{
// 			previous = tkn;
// 			tkn = tkn -> next;
// 		}
// 	}

// }


static void token_list_without_spaces(t_shell *shell)
{
    t_token *tkn = shell->token;
    t_token *prev = NULL;
    t_token *tmp;
    char *new_value;

    while (tkn)
    {
        if (tkn->type == TK_SPACE)
        {
            tmp = tkn;
            tkn = tkn->next;

            if (prev)
                prev->next = tkn;
            else
                shell->token = tkn;

            free(tmp->value);
            free(tmp);
        }
        else if (tkn->next && tkn->next->type != TK_SPACE)
        {
            new_value = ft_strjoin(tkn->value, tkn->next->value);
            tkn->value = new_value;

            tmp = tkn->next;
            tkn->next = tmp->next;
            free(tmp->value);
            free(tmp);
        }
        else
        {
            prev = tkn;
            tkn = tkn->next;
        }
    }
}




int	tokenization(t_shell *shell)
{
	char			*current;

	current = shell -> input;
	if (!are_quotes_even(shell -> input))
		return (-2);
	handle_special_chars(shell, current);
	token_list_without_spaces(shell);
	//expand_heredoc(shell);
	return (0);
}


char *extract_var(char *str, t_shell *shell)
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
