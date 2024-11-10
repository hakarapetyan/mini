#include "./include/minishell.h"

static void	copy_str(char *s, char **str, size_t *i, size_t len)
{
	char	quote;
	size_t	j;

	j = 0;
	if (s)
	{
	while (*i < ft_strlen(s) && j < len)
	{
		if (is_quote(s[*i]))
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
	if (!s || len == 0)
		return (NULL);
	str = (char *)malloc(sizeof(*s) * (len + 1));
	if (!str)
		return (NULL);
	copy_str(s, &str, &i, len);
	return (str);
}

static int	handle_quote(t_shell *shell, char **current, char *quote, int *i)
{
	int	len;

	len = 0;
	(*i)++;
	while ((*current)[(*i)] && (*current)[(*i)] != *quote)
	{
		(*i)++;
		len++;
	}
	if ((*current)[(*i)] != *quote)
	{
		error(QUOTE_ERR, shell);
		return (0);
	}
	if ((*current)[(*i)] == *quote)
		(*i)++;
	return (len);
}
static	char *check_quote(t_shell *shell,char **current, int *i, char *quote)
{
	int	len;

	len = 0;
	if ((*current)[*i] && is_quote((*current)[(*i)]))
	{
		*quote = (*current)[(*i)];
		len += handle_quote(shell, current, quote, i);
		return (another_substr(*current, 0, len));
	}
	while ((*current)[(*i)] && !is_space((*current)[*i]) && !is_quote((*current)[(*i)]))
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
	if ((ft_search(var,shell)) && (quote == '"' || !quote))
	{
		res = extract_var_from_quoted_str(var,shell);
		free_arr(&var);
		return (res);
	}
	else
		return (var);
}
static int is_key_helper(t_shell *shell, char **tmp)
{
	if (is_key(shell -> env, *tmp))
	{
		free_arr(tmp);
		return(1);
	}
	else
	{
		free_arr(tmp);
		return (2);
	}
}
static int is_valid_var(char **str,t_shell *shell, int i)
{
	char	*tmp;

	tmp = NULL;
	while ((*str)[i])
	{
		while (*(*str) != '$' && *(*str))
			(*str)++;
		if (!(*str) || !(**str))
			break;
		(*str)++;
		if (!(*str) || !(**str))
			break;
		while ((*str)[i] && !is_space((*str)[i]) && (*str)[i] != '$' && !is_quote((*str)[i]))
			i++;
		tmp = ft_strdup_interval(str, &i);
		return(is_key_helper(shell, &tmp));
	}
	free_arr(&tmp);
	return (0);
}
int	 ft_search(char	*str, t_shell *shell)
{
	int	i;
	int val;

	i = 0;
	val = 0;
	if (!(shell -> env) || !str)
		return (0);
	if(ft_strchr(str, '$'))
	{
		val = is_valid_var(&str, shell, i);
		if (val == 1)
			return (1);
		else if (val == 2)
			return (2);
	}
	return (0);
}

char	*extract_var_from_quoted_str(char *str, t_shell *shell)
{
	char	*res;
	char	*tmp;
	int		i;

	i = 0;
	res = NULL;
	tmp = NULL;
	if (!shell -> env || !str)
		return (NULL);
	while (*str)
	{
		if (str[i] != '$')
		{
			while (str[i] && str[i] != '$')
				i++;
			tmp = ft_strdup_interval(&str, &i);
			res = ft_strjoin(res, tmp);
			free(tmp);
			tmp = NULL;
		}
		else if(str[i] == '$' && !is_quote(str[i + 1]))
		{
			tmp = var_in_quotes(shell, &str);
			res = ft_strjoin(res, tmp);
			free(tmp);
			tmp = NULL;
		}
	}
	return (res);
}


static	char *var_in_quotes_helper(char **str, int *len)
{
	int	i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	(*str)++;
	while ((*str)[(*len)] && (ft_isalnum((*str)[(*len)]) || (*str)[(*len)] == '_'))
		(*len)++;
	tmp = malloc(sizeof(char) * ((*len) + 1));
	if (!tmp)
		return (NULL);
	while(i != (*len))
	{
		tmp[i] = (*str)[i];
		i++;
	}
	tmp[i] = '\0';
	(*str) += (*len);
	return (tmp);
}

char	*var_in_quotes(t_shell *shell, char **str)
{
	int len;
	char	*tmp;
	char	*res;

	len = 0;
	tmp = NULL;
	res = NULL;
	if ((*str)[len] == '$' && !((*str)[len + 1]))
	{
		(*str)++;
		return (ft_strdup("$"));
	}
	tmp = var_in_quotes_helper(str, &len);
	if (!tmp)
		return (NULL);
	res = is_key(shell -> env, tmp);
	free_arr(&tmp);
	if (!res)
		return (ft_strdup(""));
	return (ft_strdup(getenv(res)));
}
