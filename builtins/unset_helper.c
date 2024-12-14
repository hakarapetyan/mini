/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:33:37 by hakarape          #+#    #+#             */
/*   Updated: 2024/12/14 17:24:03 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	  my_strchr(char *s, int c)
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
    	if (arg[i] == '+' || arg[i] == '-' || (arg[i] >= 48 && arg[i] <= 57))
			return (0);
		else
			i++;
    	while (arg[i] && arg[i] != '=')
    	{
    	    if (my_isalnum(arg[i]) || arg[i] == '_')
    	        i++;
    	    else
    	    	return (0);
    	}
		return (1);
    }
    return (0);
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
	ft_putendl_fd(msg, fd);
	write(fd, "`", 1);
	ft_putendl_fd(arg, fd);
	write(fd, "'", 1);
}
