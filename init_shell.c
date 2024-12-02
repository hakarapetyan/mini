#include "./include/minishell.h"

void	init_data(env_list **data)
{
	(*data) -> key = NULL;
	(*data) -> value = NULL;
	(*data) -> next = NULL;
}
void	init_shell(t_shell *shell)
{
	shell -> pwd = NULL;
	shell -> oldpwd = NULL;
	shell -> input = NULL;
	shell -> shlvl = 0;
	shell -> token_count = 0;
	shell -> next = NULL;
	shell -> token = NULL;
	shell -> command = NULL;
	shell -> flag = 0;
	// init_data(&shell -> env);
	// init_data(&shell -> exp);
}

