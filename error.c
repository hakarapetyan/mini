#include "./include/minishell.h"

void	error(char	*err, t_shell *shell)
{
	printf("%s\n", err);
	//free_shell(shell);
	// system("leaks minishell");
	//exit(1);
}
