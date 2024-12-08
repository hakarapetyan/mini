/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:43:58 by ashahbaz          #+#    #+#             */
/*   Updated: 2024/12/05 16:25:10 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./include/minishell.h"

static int	create_first_command(t_token **tkn, t_commands **tmp, t_shell *shell)
{
	if (((*tkn) -> value && (*(*tkn) -> value) != '\0') || ((*tkn) -> state != DEFAULT
		&& (*tkn) -> value && (*(*tkn) -> value) == '\0'))
	{
		*tmp = create_command((*tkn) -> value);
		shell -> command = *tmp;
		if (!(shell -> command))
			error(ALLOCATION_ERR, shell);
		shell -> command_count++;
		return (0);
	}
	return (-1);
}

int	create_commands(t_shell *shell)
{
	t_token		*tkn;
	t_commands	*tmp;

	// if (!shell -> token)
	// 	error(ALLOCATION_ERR, shell);
	tmp = shell -> command;
	tkn = shell -> token;
	if (tkn)
	{
		while (tkn)
		{
			if (!tmp)
			{
				if	(create_first_command(&tkn, &tmp, shell) < 0)
					return (-1);
			}
			else
				add_command(&tkn, &tmp, shell);
			if (get_args(&tkn, shell) < 0)
				return (-1);
		}
	}
	return (0);
}


void	add_command(t_token **tkn, t_commands **tmp, t_shell *shell)
{
	if (!ft_strcmp((*tkn) -> value, "|"))
	{
			while ((*tmp) -> next)
				(*tmp) = (*tmp) -> next;
			(*tmp) -> next = create_command((*tkn) -> next -> value);
			if (!((*tmp) -> next))
				free_shell(shell);
			(*tmp) -> next -> prev = *tmp;
			(*tkn) = (*tkn) -> next;
			(*tmp) = (*tmp) -> next;
			shell -> command_count++;
	}
}


t_commands	*create_command(char *value)
{
	t_commands	*command;

	if (!value)
		return (NULL);
	command = malloc(sizeof(t_commands));
	if (!command)//allocation failed;
		return (NULL);
	command -> r_in = NULL;
	command -> r_out = NULL;
	command -> r_heredoc = NULL;
	command -> is_append = 0;
	command -> name = NULL;
	command -> args = NULL;
	command -> next = NULL;
	command -> prev = NULL;
	command -> state = DEFAULT;
	command -> heredoc_count = 0;
	command -> fd_in = 0;
	command -> fd_out = 0;
	command -> stdin_original = dup(STDIN_FILENO);
	command -> stdout_original = dup(STDOUT_FILENO);
	if (!command)
	{
		free_commands(command);
		return (NULL);//alocation failed
	}
	command -> next = NULL;
	return (command);
}

