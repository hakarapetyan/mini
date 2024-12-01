#include "./include/minishell.h"


// //freeee pathnmae it would give leaks 
static int handle_input_redirection(t_shell *shell, char **pathname)
{
    if (shell->command->r_heredoc)
    {
        shell->command->fd_in = open("tmp_file", O_RDONLY);
        if (shell->command->fd_in < 0)
        {
            free(*pathname);
            error_message(1, "tmp_file");
            return (-1);
        }
    }
    else if (shell->command->r_in)
    {
                printf("am i in input\n");
        shell->command->fd_in = open(shell->command->r_in, O_RDONLY);
        if (shell->command->fd_in < 0)
        {
            free(*pathname);
            error_message(1, shell->command->r_in);
            return (-1);
        }
    }
    return (0);
}

static int setup_input_fd(t_shell *shell, char **pathname)
{
    if (shell->command->fd_in >= 0)
    {
                printf("am i in input dup\n");

        if (dup2(shell->command->fd_in, STDIN_FILENO) < 0)
        {
            error_message(1, "dup2 error");
            close(shell->command->fd_in);
            return (-1);
        }
        close(shell->command->fd_in);
    }
    return (0);
}

static int handle_output_redirection(t_shell *shell, char **pathname)
{
        printf("am i in output\n");
    if (shell->command->is_append)
        shell->command->fd_out = open(shell->command->r_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
    else if (shell->command->r_out)
    {
        shell->command->fd_out = open(shell->command->r_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (shell->command->fd_out < 0)
        {
            free(*pathname);
            error_message(1, shell->command->r_out);
            return (-1);
        }
    }
    return (0);
}

static int setup_output_fd(t_shell *shell, char **pathname)
{
    if (shell->command->fd_out >= 0)
    {

        printf("am i in output dup\n");
        if (dup2(shell->command->fd_out, STDOUT_FILENO) < 0)
        {
            free(*pathname);
            error_message(1, shell->command->r_out);
            close(shell->command->fd_out);
            return (-1);
        }
        close(shell->command->fd_out);
    }
    return (0);
}

int prepare_redirections(t_shell *shell, char **pathname)
{
    if (handle_input_redirection(shell, pathname) < 0)
        return (-1);
    if (setup_input_fd(shell, pathname) < 0)
        return (-1);
    if (handle_output_redirection(shell, pathname) < 0)
        return (-1);
    if (setup_output_fd(shell, pathname) < 0)
        return (-1);
    return (0);
}



// int 	prepare_redirections(t_shell *shell, char **pathname)
// {
// 	if (shell->command->r_heredoc)
// 	{
// 		shell->command->fd_in = open("tmp_file", O_RDONLY);
// 		if (shell->command->fd_in < 0)
// 		{
// 			//free(*pathname);
// 			error_message(1, "tmp_file");
// 			///exit(EXIT_FAILURE);
// 		}
// 	}
// 	else if (shell->command->r_in)
// 	{
// 		shell->command->fd_in = open(shell->command->r_in, O_RDONLY);
// 		if (shell->command->fd_in < 0) {
// 			//free(*pathname);
// 			printf("fuvk\n");
// 			error_message(1, shell->command->r_in);
// 			return (-1);
// 						//exit(EXIT_FAILURE);
// 		}
// 	}
// 	if (shell->command->fd_in >= 0)
// 	{
// 		if (dup2(shell->command->fd_in, STDIN_FILENO) < 0)
// 		{
// 			free(*pathname);
// 			error_message(1, "dup2 error");
// 			close(shell->command->fd_in);
// 			//exit(EXIT_FAILURE);
// 		}
//     	close(shell->command->fd_in);
// 	}
// 	if (shell->command->is_append)
// 		shell->command->fd_out = open(shell->command->r_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 	else if (shell->command->r_out)
// 	{
// 		shell->command->fd_out = open(shell->command->r_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		if (shell->command->fd_out < 0)
// 		{
// 			//free(*pathname);
// 			error_message(1, shell -> command -> r_out);
// 			// if (pathname)
// 			// free(pathname);
// 			//exit(EXIT_FAILURE);
// 		}
// 		if (shell->command->fd_out >= 0)
// 		{
// 			if (dup2(shell->command->fd_out, STDOUT_FILENO) < 0)
// 			{
// 				free(*pathname);
// 				error_message(1, shell -> command -> r_out);
// 				close(shell->command->fd_out);
// 				// if (pathname)
// 				// free(pathname);
// 				//exit(EXIT_FAILURE);
// 			}
// 			close(shell->command->fd_out);
// 		}
// 	}
// } 