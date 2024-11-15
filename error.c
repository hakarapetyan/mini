#include "./include/minishell.h"

void	error(char	*err, t_shell *shell)
{
	printf("%s\n", err);
	//free_shell(shell);
	// system("leaks minishell");
	//exit(1);
}

void	permission_error(char *name)
{
	char	*message;

	message = ": Permission denied";
	write(2, "bash: ", 7);
	write(2, name, ft_strlen(name));
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	return ;
}

void	no_such_file_error(char *name)
{
	char	*message;

	message = ": No such file or directory";
	write(2, "bash: ", 7);
	write(2, name, ft_strlen(name));
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	return ;
}
void syntax_error(char *message)
{
	char	*str;

	str = "syntax error near unexpected token `";
	write(2, str, ft_strlen(str));
	write(2, message, ft_strlen(message));
	write(2, "'\n", 2);
	return ;
}
