/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 21:36:16 by hakarape          #+#    #+#             */
/*   Updated: 2024/12/15 19:43:55 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

static void in_ctrl(int num)
{
	set_status(FAILURE);
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)num;
}
static void nonin_ctrl(int num)
{
	//write(1, "\n", 1);
	(void)num;
}
static void b_slash(int num)
{
	// if (isatty(STDERR_FILENO))
    //     ft_putendl_fd("Quit: 3\n", 2);
	ft_putendl_fd("Quit: 3\n", 2);
	(void)num;
}
static void h_ctrl(int num)
{
	(void)num;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	if (get_status() == 222)
		write(STDIN_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	set_status(222);
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
