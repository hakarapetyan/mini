/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_buil.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakarape <hakarape@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:43:28 by hakarape          #+#    #+#             */
/*   Updated: 2024/11/18 16:10:46 by hakarape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	ft_lstsize(env_list *lst)
{
	int	count;

	count = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		count++;
		lst = lst -> next;
	}
	return (count);
}