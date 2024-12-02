/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:13:25 by ashahbaz          #+#    #+#             */
/*   Updated: 2024/12/02 14:13:25 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./include/minishell.h"

static void	allocate_args(t_commands **cmd, int count, t_shell *shell)
{
	int i;

	i = 0;
	if (!cmd || !(*cmd))
        return;
	(*cmd) -> args = malloc(sizeof(char *) * (count + 1));
	if (!(*cmd) -> args)
		error(ALLOCATION_ERR, shell);
	while (i < count)
	{
		(*cmd) -> args[i] = NULL;
		i++;
	}
	(*cmd) -> args[i] = NULL;
}


static void add_args_helper(t_commands **tmp, int *i)
{
    if (!tmp || !(*tmp))
        return;
    if ((*tmp) -> args[0])
        (*tmp) -> name = ft_strdup((*tmp) -> args[0]);
    else
        (*tmp) -> name = NULL;
    if ((*tmp) -> args)
        (*tmp) -> args[*i] = NULL;
    (*tmp) = (*tmp) -> next;
}



static void	add_args(t_token **token,t_commands **tmp,  t_shell *shell)
{
	int	i;

	i = 0;
	while ((*token) && (*token) -> type != PIPE)
	{
		if (is_redirection((*token) -> type))
			get_redir(token, tmp, shell);
		if ((*token) && (!is_redirection((*token) -> type) && (*token) -> type != PIPE))
		{
			if (*((*token) -> value) == '\0' && (*token) -> state == 2)
				(*tmp) -> args[i] = ft_strdup(" ");
			else
				(*tmp) -> args[i] = ft_strdup(((*token)) -> value);
			if (!(*tmp) -> args[i])
				error(ALLOCATION_ERR, shell);
			(*token) = (*token) -> next;
			i++;
		}
	}
    add_args_helper(tmp, &i);
}

void get_args(t_token **token, t_shell *shell)
{
	t_commands	*tmp;

	tmp = shell -> command;
    if (!token || !*token || !shell || !shell->token)
        return;
	if (!tmp)
		return ;
	while (tmp -> next)
		tmp = tmp -> next;
	if (tmp -> args)
		return ;
	allocate_args(&tmp, args_count(token), shell);
	add_args(token,&tmp, shell);
}
