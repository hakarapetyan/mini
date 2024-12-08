/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_status.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakarape <hakarape@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 15:52:20 by ashahbaz          #+#    #+#             */
/*   Updated: 2024/12/08 15:10:15 by hakarape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./include/minishell.h"

int	g_exit_status;

void set_status(int status)
{
	g_exit_status = status;
}
int get_status(void)
{
	return (g_exit_status);
}
