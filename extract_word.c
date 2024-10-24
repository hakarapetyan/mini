#include "./include/minishell.h"

static char	*another_substr(char *s, unsigned int start, size_t len, char *quote)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = start;
	j = 0;
	if (!s)
		return (NULL);
	str = (char *)malloc(sizeof(*s) * (len + 1));
	if (!str)
		return (NULL);
		printf("quote from start= %c\n" ,*quote);
	while (i < ft_strlen(s) && j < len)
	{
		if (s[i] != *quote)
		{
			printf("%c\n",s[i]);
			str[j++] = s[i++];
			if (is_quote(s[i]))
				*quote = s[i];
		}
		else
		{
			//*quote = s[i];
			i++;
		printf("quote = %c\n" ,*quote);//"hi"'th'
		}
	}
	str[j] = '\0';
	printf(">>%s\n",str);
	return (str);
}

// char	*extract_word(char **current, t_shell *shell)
// {
// 	//char	quote;
// 	char	*var;
// 	char	*res;
// 	int	i;

// 	i = 0;
// 	var = NULL;
// 	if (**current && is_quote(**current))
// 		var = extract_quoted_str(current, shell);
// 	else if (**current)
// 	{
		// while ((**current) && (is_space(**current)))
		// 	(*current)++;
// 		while ((*current)[i] && (!(is_space((*current)[i]))))
// 			i++;
// 		if (i > 0)
// 		{
// 			var = another_substr(*current, 0, i);
// 			if (!var)
// 				return (NULL);
// 			*current += i;
// 		}
// 	}
// 	printf("here %s\n",var);
// 	if ((ft_search(var,shell)))
// 	{
// 		res = extract_var_from_quoted_str(var,shell);
// 		free_arr(&var);
// 		return (res);
// 	}
// 	else
// 		return (var);
// 	// if (!var)
// 	// 			printf("\n");
// 	//return (var);
// }


static int	handle_quote(char **current, char *quote, int *i)
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
		return (0);
	(*i)++;
	printf("lnnnnnn%c\n",(*current)[(*i)]);
	return (len);
}
static	char *check_quote(char **current, int *i, char *quote)
{
	int	len;
	char	*res;
	char	*tmp;

	len = 0;
	res = NULL;
	while ((*current)[*i] && !is_space((*current)[(*i)]))
	{
		if (is_quote((*current)[*i]))
		{
			*quote = (*current)[(*i)];
			printf("checkic %c\n",*quote);
			len += handle_quote(current, quote, i);
			tmp = another_substr(*current, 0, len, quote);
			res = ft_strjoin(res, tmp);
			printf("ressss = %s\n",*current);
		}
		else
		{
			while ((*current)[(*i)] && (ft_isalnum((*current)[*i]) || (*current)[*i] == '_'))
			{
				printf("str = %c\n", (*current)[(*i)]);
				(*i)++;
				len++;
			}
			tmp = another_substr(*current, 0, len, quote);
			res = ft_strjoin(res, tmp);
		}
		free(tmp);
		tmp = NULL;
		//	*current += *i;
	}
	printf("i -> %d\n",*i);
	return (res);
}
char	*extract_word(char **current, t_shell *shell)
{
	int	i;
	char	quote;
	char	*var;
	char	*res;

	i = 0;
	quote = '\0';
	while ((**current) && (is_space(**current)))
		(*current)++;
	var = check_quote(current, &i, &quote);
	if (!var)
		return (NULL);
	*current += i;

	if ((ft_search(var,shell)) && (quote == '"' || !quote))
	{
		res = extract_var_from_quoted_str(var,shell);
		free_arr(&var);
		return (res);
	}
	else
	{
		return (var);
	}
}

char	*extract_quoted_str(char **current, t_shell *shell)
{
	char quote;
	int	i;
	char	*var;
	char	*res;

	i = 0;
	var = NULL;
	quote = **current;
	(*current)++;
	if (**current == quote)
	{
		(*current)++;
		return (NULL);
	}
	// while ((**current) && (is_space(**current)))
	// 	(*current)++;
	while ((*current)[i] && ((*current)[i] != quote))
		i++;
	if (i > 0)
		var = ft_substr(*current, 0, i);
	if (!var)
		return (NULL);
	*current += i;
	while ((**current) && (is_space(**current)))
		(*current)++;
	if ((**current) == quote)
		(*current)++;
	if ((ft_search(var,shell)) && quote == '"')
	{

		res = extract_var_from_quoted_str(var,shell);
		free_arr(&var);
		return (res);
	}
	else
	{
		return (var);
	}
}
static int is_valid_var(char **str,t_shell *shell, int i, int j)
{
	char	*tmp;

	tmp = NULL;
	(void)j;
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
		//j = i + 1;
		tmp = ft_strdup_interval(str, &i);
		if (is_key(shell -> env, tmp))
		{
			free_arr(&tmp);
			return(1);
		}
		else
		{
			free_arr(&tmp);
			return (2);
		}
	}
	free_arr(&tmp);
	return (0);
}
int	 ft_search(char	*str, t_shell *shell)
{
	int	i;
	int	j;
	int val;

	i = 0;
	j = 0;
	val = 0;
	if (!(shell -> env) || !str)
		return (0);
	if(ft_strchr(str, '$'))
	{

		val = is_valid_var(&str, shell, i, j);
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
	if (!shell -> env)
		return (NULL);
	while (*str)
	{
		printf("str = [%s]\n",str);
		if (str[i] != '$')
		{
			while (str[i] && str[i] != '$')
				i++;
			tmp = ft_strdup_interval(&str, &i);
			res = ft_strjoin(res, tmp);
		}
		else if(str[i] == '$' && !is_quote(str[i + 1]))
		{
			tmp = var_in_quotes(shell, &str);
			res = ft_strjoin(res, tmp);
		}
		free(tmp);
		tmp = NULL;
	}
	return (res);
}


char	*var_without_quotes(t_shell *shell, char **str)
{
	int i;
	int len;
	char	*tmp;
	char	*res;

	i = 0;
	len = 0;
	tmp = NULL;
	res = NULL;
	if ((*str)[len] == '$' && !((*str)[len + 1]))
	{
		(*str)++;
		return (ft_strdup("$"));
	}
	(*str)++;
	while ((*str)[len] && (ft_isalnum((*str)[len]) || (*str)[len] == '_'))
		len++;
	printf("len = %d\n",len);
	tmp = malloc(sizeof(char) * (len + 1));
	if (!tmp)
		return (NULL);

	while(i != len)
	{
		tmp[i] = (*str)[i];
		i++;
	}
	tmp[i] = '\0';
	(*str) += len;
	res = is_key(shell -> env, tmp);
	free_arr(&tmp);
	if (!res)
		return (ft_strdup(""));
	return (ft_strdup(getenv(res)));
}

char	*var_in_quotes(t_shell *shell, char **str)
{
	int i;
	int len;
	char	*tmp;
	char	*res;

	i = 0;
	len = 0;
	tmp = NULL;
	res = NULL;
	if ((*str)[len] == '$' && !((*str)[len + 1]))
	{
		(*str)++;
		return (ft_strdup("$"));
	}
	(*str)++;
	while ((*str)[len] && (ft_isalnum((*str)[len]) || (*str)[len] == '_'))
		len++;
	tmp = malloc(sizeof(char) * (len + 1));
	if (!tmp)
		return (NULL);
	while(i != len)
	{
		tmp[i] = (*str)[i];
		i++;
	}
	tmp[i] = '\0';
	(*str) += len;
	res = is_key(shell -> env, tmp);
	free_arr(&tmp);
	if (!res)
		return (ft_strdup(""));
	return (ft_strdup(getenv(res)));
}
