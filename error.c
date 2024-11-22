#include "./include/minishell.h"

void	error(char	*err, t_shell *shell)
{
	printf("%s\n", err);
	//free_shell(shell);
	// system("leaks minishell");
	//exit(1);
}


static void which_errno(void)
{
	if (errno == ENOENT)
		write(STDERR_FILENO, NO_SUCH_FILE_MSG, ft_strlen(NO_SUCH_FILE_MSG));
	else if (errno == EACCES)
		write(STDERR_FILENO, PERMISSION_DENIED_MSG, ft_strlen(PERMISSION_DENIED_MSG));
	else if (errno == EISDIR)
		write(STDERR_FILENO, IS_DIRECTORY_MSG, ft_strlen(IS_DIRECTORY_MSG));
	else if (errno == ENOTDIR)
		write(STDERR_FILENO, NOT_DIRECTORY_MSG, ft_strlen(NOT_DIRECTORY_MSG));
}


void	error_message(int status, char *command_name)
{
	set_status(status);
	if (command_name)
	{
		write(STDERR_FILENO, "minishell: ", 11);
		write(STDERR_FILENO, command_name, ft_strlen(command_name));
		write(STDERR_FILENO, ": ", 2);
		which_errno();
	}
	write(STDERR_FILENO, "\n", 1);
	return ;
}

void	simple_error(int status, char *command_name, char *message)
{
	set_status(status);
	if (command_name)
	{
		write(STDERR_FILENO, "minishell: ", 11);
		write(STDERR_FILENO, command_name, ft_strlen(command_name));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, message, ft_strlen(message));
	}
	write(STDERR_FILENO, "\n", 1);
	return ;
}

void	syntax_error(char *message)
{
	char	*str;

	str = "syntax error near unexpected token `";
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, message, ft_strlen(message));
	write(STDERR_FILENO, "'\n", 2);
	return ;
}
