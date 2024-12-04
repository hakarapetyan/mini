/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 16:11:29 by hakarape          #+#    #+#             */
/*   Updated: 2024/12/05 01:37:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	my_strchr(const char *s, int c)
{
	int	i;

	i = 0;
    if (s[i] != '=')
    {
	while (s[i] && s[i] != '=')
	{
		if (s[i] == c)
			return (1);
		i++;
	}
    if(s[i] == '=' || !ft_strchr(s, '='))
        return (1);
    }
	return (0);
}

int is_alpha(char *arg)
{
    int i;
    
    i = 0;
    if (arg[i] != '=')
    {
    if (arg[i] == '+' || arg[i] == '-')
		i++;
    while (arg[i] && arg[i] != '=')
    {
        if ((arg[i] >= 65 && arg[i] <= 90) || (arg[i] >= 97 && arg[i] <= 122) || arg[i] == '_')
            i++;
        else
        	return (0);
    }
    }
    return (1);
}
int is_digit_unset(char *arg)
{
    int i;
    
    i = 0;
    if (arg[i] == '+' || arg[i] == '-')
		i++;
    while (arg[i])
    {
        if (arg[i] >= 48 && arg[i] <= 57)
            i++;
        else
        return (1);
    }
    return (0);
}
void write_print(char *arg, char * msg, int fd)
{
	ft_putendl_fd(msg, 2);
	write(2, "`", 1);
	ft_putendl_fd(arg, 2);
	write(2, "'", 1);
}