#include "./include/minishell.h"

int	is_space(int c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	ft_isalnum(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	if (c >= 48 && c <= 57)
		return (2);
	return (0);
}

int	is_separator(char c)
{
	if((c == '<') || (c == '>') || (c == '|') || (c == '$'))
		return (1);
	return (0);
}
int	is_quote(char c)
{
	if((c == '\"') || (c == '\''))
		return (1);
	return (0);
}

int	are_quotes_even(char *str)
{
	int	count_s;
	int	count_d;
	int	i;

	i = 0;
	count_s = 0;
	count_d = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			count_s++;
		else if (str[i] == '\"')
			count_d++;
		i++;
	}
	if ((count_s % 2) == 0 && (count_d % 2) == 0)
		return (1);
	return (0);
}
