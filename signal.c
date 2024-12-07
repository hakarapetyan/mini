/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakarape <hakarape@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 21:36:16 by hakarape          #+#    #+#             */
/*   Updated: 2024/12/07 23:05:37 by hakarape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

static void in_ctrl(int num)
{
	set_status(FAILURE);
	write(1, "\n", 1);
	rl_replace_line("", 0);
	(void)num;
}
static void nonin_ctrl(int num)
{
	write(1, "\n", 1);
	(void)num;
}
static void b_slash(int num)
{
	ft_putendl_fd("Quit: 3\n", 2);
	(void)num;
}
static void h_ctrl(int num)
{
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	set_status(FAILURE);
	(void)num;
}

void signals(int num)
{
	if (num == INTERACTIVE)
	{
		signal(SIGINT, in_ctrl);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (num == NINTERACTIVE)
	{
		signal(SIGINT, nonin_ctrl);
		signal(SIGQUIT, b_slash);
	}
	else if (num == HEREDOC)
	{
		signal(SIGINT, h_ctrl);
		signal(SIGQUIT, SIG_IGN);
	}
}