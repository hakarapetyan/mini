/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakarape <hakarape@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:03:53 by hakarape          #+#    #+#             */
/*   Updated: 2024/12/11 18:36:30 by hakarape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_nbr(const char *str)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	while ((str[i] >= '0' && str[i] <= '9') && str[i])
	{
		n = n * 10 + (str[i] - '0');
		i++;
	}
	return (n);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	count;

	sign = 1;
	i = 0;
	count = 0;
	while (((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			sign = -1;
			count++;
		}
		else if (str[i] == '+')
			count++;
		i++;
	}
	if (count > 1)
		return (0);
	return (ft_nbr(&str[i]) * sign);
}

int exit_status(char *argv)
{
	long num;
	int tmp;
	if (!argv)
		return (0);
	num = ft_atoi(argv);
	if (num >= 0)
		return (num % 256);
	else if (num < 0)
	{
	    tmp = num % 256;
	   if (tmp)
	    tmp = tmp + 256;
	   else
	    return (tmp);
	return (tmp);
	}
	return (0);
}