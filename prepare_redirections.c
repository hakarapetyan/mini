/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:13:48 by ashahbaz          #+#    #+#             */
/*   Updated: 2024/12/02 14:13:48 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./include/minishell.h"


// //freeee pathnmae it would give leaks
int handle_input_redirection(t_shell *shell, t_commands **cmd)
{
    if ((*cmd)->r_heredoc)
    {

		heredoc_handle(shell,cmd);
        (*cmd)->fd_in = open("tmp_file", O_RDONLY);
        if ((*cmd)->fd_in < 0)
        {
			//(*cmd) -> error_message = ft_strdup()
            error_message(1, "tmp_file");
            return (-1);
        }
    }
    else if ((*cmd)->r_in)
    {
        (*cmd)->fd_in = open((*cmd)->r_in, O_RDONLY);

        if ((*cmd)->fd_in < 0)
        {
		//	(*cmd) -> error = ft_strdup((*cmd) -> r_in);
            error_message(1, (*cmd)->r_in);
            return (-1);
        }
    }
    return (0);
}

static int setup_input_fd(t_shell *shell, t_commands  *cmd)
{
    if (cmd->fd_in >= 0)
    {
		if (shell -> command -> r_heredoc && get_status() == 222)
		{
        	set_status(1);
			close(shell->command->fd_in);
			return (-1);
		}
        if (dup2(cmd->fd_in, STDIN_FILENO) < 0)
        {
            error_message(1, cmd->r_in);
            close(cmd->fd_in);
            return (-1);
        }
        close(cmd->fd_in);
    }
    return (0);
}

int handle_output_redirection(t_shell *shell, t_commands **cmd)
{
    if ((*cmd)->is_append)
	{
        (*cmd)->fd_out = open((*cmd)->r_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if ((*cmd)->fd_out < 0)
        {
            error_message(1, (*cmd)->r_out);
            return (-1);
        }
	}
    else if ((*cmd)->r_out)
    {
        (*cmd)->fd_out = open((*cmd)->r_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if ((*cmd)->fd_out < 0)
        {
            error_message(1, (*cmd)->r_out);
            return (-1);
        }
    }
    return (0);
}

static int setup_output_fd(t_shell *shell, t_commands *cmd)
{

    if (cmd->fd_out >= 0)
    {
        if (dup2(cmd->fd_out, STDOUT_FILENO) < 0)
        {
            error_message(1, cmd->r_out);
            close(cmd->fd_out);
            return (-1);
        }
        close(cmd->fd_out);
    }
    return (0);
}

int prepare_redirections(t_shell *shell, t_commands *cmd)
{
    if (setup_input_fd(shell, cmd) < 0)
        return (-1);
    if (setup_output_fd(shell, cmd) < 0)
        return (-1);
    return (0);
}



