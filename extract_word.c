/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:43:28 by ashahbaz          #+#    #+#             */
/*   Updated: 2024/12/10 15:45:53 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./include/minishell.h"

static void	copy_str(char *s, char **str, size_t *i, size_t len)
{
	char	quote;
	size_t	j;

	j = 0;
	if (s)
	{
		//printf("%d\n", ft_strlen(s));
		while (*i < ft_strlen(s) && j < len)
		{
			if (s[*i] && is_quote(s[*i]))
			{
				quote = s[*i];
				(*i)++;
				while (s[*i] && s[*i] != quote)
					(*str)[(j)++] = s[(*i)++];
				(*i)++;
			}
			else
				(*str)[j++] = s[(*i)++];
		}
		(*str)[j] = '\0';
	}
}


static char	*another_substr(char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = start;
	if (!s)
		return (NULL);
	str = (char *)malloc(sizeof(*s) * (len + 1));
	if (!str)
		return (NULL);
	copy_str(s, &str, &i, len);
	return (str);
}
static void handle_quote_helper(char *quote)
{
	if (*quote == '"')
		syntax_error("\"");
	if (*quote == '\'')
		syntax_error("'");
}
static int	handle_quote(t_shell *shell, char **current, char *quote, int *i)
{
	int	len;

	len = 0;
	(void)shell;
	(*i)++;
	if (((*current)[(*i)] && (*current)[(*i)] == '\0') || !((*current)[(*i)]))
	{
		handle_quote_helper(quote);
		return (-1);
	}
	while ((*current)[(*i)] && (*current)[(*i)] != *quote )
	{
		(*i)++;
		len++;
	}
	if ((*current)[(*i)] != *quote)
	{
		handle_quote_helper(quote);
		return (-1);
	}
	if ((*current)[(*i)] == *quote)
		(*i)++;
	return (len);
}
static	char *check_quote(t_shell *shell,char **current, int *i, char *quote)
{
	int	len;
	int n;

	len = 0;
	n = 0;
	if ((*current)[*i] && is_quote((*current)[(*i)]))
	{
		*quote = (*current)[(*i)];
		n = handle_quote(shell, current, quote, i);
		if (n >= 0)
			len += n;
		else
			return (NULL);
		return (another_substr(*current, 0, len));
	}
	while ((*current)[(*i)] && !is_space((*current)[*i]) && !is_quote((*current)[(*i)]) && !is_sep((*current)[*i]))
	{
		(*i)++;
		len++;
	}
	return (another_substr(*current, 0, len));
}



char	*extract_word(char **current, t_shell *shell)
{
	int	i;
	char	quote;
	char	*var;
	char	*res;

	i = 0;
	quote = '\0';
	var = check_quote(shell, current, &i, &quote);
	if (!var)
	{
		*current += i;
		return (NULL);
	}
	*current += i;
	if ((var_search(var,shell)) && (quote == '"' || !quote))
	{
		if (get_the_token_i_want(shell) &&  get_the_token_i_want(shell)-> type == R_HEREDOC)
			return (var);
		res = extract_var(var,shell);
		free_arr(&var);
		return (res);
	}
	else
		return (var);
}









