/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_status.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 15:52:20 by ashahbaz          #+#    #+#             */
/*   Updated: 2024/11/24 15:52:21 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./include/minishell.h"


int	g_exit_status;


void set_status(int status)
{
	g_exit_status = status;
	printf("%d\n",g_exit_status);
}
int get_status(void)
{
	return (g_exit_status);
}
