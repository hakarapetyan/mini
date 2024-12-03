/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analyzer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 15:53:12 by ashahbaz          #+#    #+#             */
/*   Updated: 2024/12/02 15:16:35 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void  lexical_analyzer(t_shell *shell)
{
	int	status;

	status = tokenization(shell);
	if (status == -2)
		error("quote error", shell);
}


void	handle_special_chars(t_shell *shell, char *current)
{
	t_lexer_state	state;

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
		// else if (*current == '$')
		// 	add_token(shell, ENV_VAR, state, extract_word(&(current),shell));
		else if (!(is_sep(*current)) && !(is_space(*current)))
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
static void	tk_space_remove(t_shell *shell, t_token **tkn, t_token **tmp, t_token **prev)
{
	*tmp = (*tkn);
	(*tkn) = (*tkn) -> next;

	if (*prev)
		(*prev) -> next = (*tkn);
	else
		shell -> token = (*tkn);

	free((*tmp)->value);
	free(*tmp);
}
static void token_list_without_spaces(t_shell *shell)
{
    t_token *tkn = shell->token;
    t_token *prev = NULL;
    t_token *tmp;
    char *new_value;

    while (tkn)
    {
        if (tkn -> type == TK_SPACE)
			tk_space_remove(shell, &tkn, &tmp, &prev);
        //else if (tkn -> next && tkn -> next -> type != TK_SPACE )
        else if ((tkn -> type == WORD || tkn -> type == ENV_VAR) && tkn -> next && (tkn -> next -> type == WORD || tkn -> next -> type == ENV_VAR))
		{
            new_value = ft_strjoin(tkn -> value, tkn -> next -> value);
            tkn -> value = new_value;
            tmp = tkn -> next;
            tkn -> next = tmp -> next;
			//free(tmp -> var_value);
            free(tmp -> value);
            free(tmp);
        }
        else
        {
            prev = tkn;
            tkn = tkn -> next;
        }
    }
}




int	tokenization(t_shell *shell)
{
	char			*current;

	current = shell -> input;
	handle_special_chars(shell, current);
	// print_tokens(shell);
	// printf("\n");
	token_list_without_spaces(shell);
	token_count(shell);
	//expand_heredoc(shell);
	return (0);
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
