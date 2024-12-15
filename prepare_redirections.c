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
int handle_input_redirection(t_shell *shell)
{
    if (shell->command->r_in)
    {
        shell->command->fd_in = open(shell->command->r_in, O_RDONLY);

        if (shell->command->fd_in < 0)
        {
              // printf("am i in input\n");
            //free(*pathname);
            error_message(1, shell->command->r_in);
            return (-1);
        }
    }
    else if (shell->command->r_heredoc)
    {
		heredoc_handle(shell);
        shell->command->fd_in = open("tmp_file", O_RDONLY);
        if (shell->command->fd_in < 0)
        {
            error_message(1, "tmp_file");
            return (-1);
        }
    }
    return (0);
}

static int setup_input_fd(t_shell *shell)
{
    if (shell->command->fd_in >= 0)
    {
             //   printf("am i in input dup\n");
		if (shell -> command -> r_heredoc && get_status() == 222)
		{
        	set_status(1);
			close(shell->command->fd_in);
			return (-1);
		}
        if (dup2(shell->command->fd_in, STDIN_FILENO) < 0)
        {
            error_message(1, shell->command->r_in);
            close(shell->command->fd_in);
            return (-1);
        }
        close(shell->command->fd_in);
			// printf("sjfod\n");
    }
    return (0);
}

int handle_output_redirection(t_shell *shell)
{
    if (shell->command->is_append)
        shell->command->fd_out = open(shell->command->r_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
    else if (shell->command->r_out)
    {
        shell->command->fd_out = open(shell->command->r_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (shell->command->fd_out < 0)
        {
            error_message(1, shell->command->r_out);
            return (-1);
        }
    }
    return (0);
}

static int setup_output_fd(t_shell *shell)
{

    if (shell->command->fd_out >= 0)
    {
     //shell -> original_stdout = dup(STDOUT_FILENO);
       // printf("am i in output dup\n");
       shell -> heredoc_flag = 1;
        if (dup2(shell->command->fd_out, STDOUT_FILENO) < 0)
        {
            error_message(1, shell->command->r_out);
            close(shell->command->fd_out);
	printf("gna\n");
            return (-1);
        }
        close(shell->command->fd_out);
    }
    return (0);
}

int prepare_redirections(t_shell *shell)
{
    // if (handle_input_redirection(shell) < 0)
	// {
    //     return (-1);
	// }
    if (setup_input_fd(shell) < 0)
        return (-1);
    // if (handle_output_redirection(shell) < 0)
    //     return (-1);
    if (setup_output_fd(shell) < 0)
        return (-1);
    return (0);
}



