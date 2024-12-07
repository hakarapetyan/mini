/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:13:31 by ashahbaz          #+#    #+#             */
/*   Updated: 2024/12/02 14:13:31 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./include/minishell.h"

static void	get_redir_helper(t_token **token,  t_shell *shell, char **type)
{
	if (*type)
		free(*type);
	if (*token && (*token) -> next)
		*type = ft_strdup((*token) -> next -> value);
	if (!(*type))
		error(ALLOCATION_ERR, shell);
}

// int	get_redir(t_token **token,t_commands **tmp,  t_shell *shell)
// {
// 	if ((*token) -> type == R_IN)
// 	{
// 		get_redir_helper(token, shell, &((*tmp) -> r_in));
// 		if (handle_input_redirection(shell) < 0)
// 			return (-1);
// 	}
// 	else if ((*token) -> type == R_OUT)
// 	{
// 		get_redir_helper(token, shell, &((*tmp) -> r_out));
// 		if (handle_output_redirection(shell) < 0)
// 			return (-1);
// 	}
// 	else if ((*token) -> type == R_APPEND)
// 	{
// 		get_redir_helper(token, shell, &((*tmp) -> r_out));
// 		(*tmp) -> is_append = 1;
// 		if (handle_output_redirection(shell) < 0)
// 			return (-1);
// 	}
// 	else if ((*token) -> type == R_HEREDOC)
// 	{
// 		get_redir_helper(token, shell, &((*tmp) -> r_heredoc));
// 		if ((*token) -> next)
// 			(*tmp) -> state = (*token) -> next -> state;
// 		(*tmp) -> heredoc_count += 1;
// 		handle_input_redirection(shell);
// 		if ((*tmp) -> heredoc_count > 16)
// 		{
// 			write(STDERR_FILENO, "minishell: maximum here-document count exceeded\n",49);
// 			clean_shell_exit(shell, 1);
// 		}
// 	}
// 	(*token) = (*token)->next ? (*token)->next->next : NULL;
// 	return (0);
// }
static int handle_input_redirection_case(t_token **token, t_commands **tmp, t_shell *shell)
{
    get_redir_helper(token, shell, &((*tmp)->r_in));
    if (handle_input_redirection(shell) < 0)
        return (-1);
    return 0;
}

static int handle_output_redirection_case(t_token **token, t_commands **tmp, t_shell *shell)
{
	//printf("barev\n");
    get_redir_helper(token, shell, &((*tmp)->r_out));
    if (handle_output_redirection(shell) < 0)
        return (-1);
    return 0;
}


static int handle_append_redirection_case(t_token **token, t_commands **tmp, t_shell *shell)
{
    get_redir_helper(token, shell, &((*tmp)->r_out));
    (*tmp)->is_append = 1;
    if (handle_output_redirection(shell) < 0)
        return (-1);
    return 0;
}


static int handle_heredoc_redirection_case(t_token **token, t_commands **tmp, t_shell *shell)
{
    get_redir_helper(token, shell, &((*tmp)->r_heredoc));
    if ((*token)->next)
        (*tmp)->state = (*token)->next->state;
    (*tmp)->heredoc_count += 1;
    handle_input_redirection(shell);
    if ((*tmp)->heredoc_count > 16)
    {
        write(STDERR_FILENO, "minishell: maximum here-document count exceeded\n", 49);
        clean_shell_exit(shell, 1);
    }
    return 0;
}

int get_redir(t_token **token, t_commands **tmp, t_shell *shell)
{
    if ((*token)->type == R_IN)
	{
        if (handle_input_redirection_case(token, tmp, shell) < 0)
			return (-1);
	}
    else if ((*token)->type == R_OUT)
	{
        if (handle_output_redirection_case(token, tmp, shell) < 0)
			return (-1);
	}
    else if ((*token)->type == R_APPEND)
	{
        if (handle_append_redirection_case(token, tmp, shell) < 0)
			return (-1);
	}
    else if ((*token)->type == R_HEREDOC)
	{
        if (handle_heredoc_redirection_case(token, tmp, shell) < 0)
			return (-1);
	}
    (*token) = (*token)->next ? (*token)->next->next : NULL;
    return 0;
}
