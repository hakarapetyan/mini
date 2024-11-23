#include "./include/minishell.h"

void	print_commands(t_shell *shell)
{
	t_commands	*current;
	int			i;

	i = 0;
	current = shell->command;
	while (current)
	{

		printf("Command: %s\n", current->name);
		if (current -> r_in)
			printf("r_in: %s\n", current->r_in);
		if (current -> r_out)
			printf("r_out: %s\n", current->r_out);
		if (current -> r_heredoc)
			printf("r_heredoc: %s\n", current->r_heredoc);
		if (current -> args)
		{
			i = 0;
			while (current -> args[i])
			{
				printf("index: %d , Args:%s \n", i, current -> args[i]);
				i++;
			}
		}
		current = current->next;
	}
}

void	print_tokens(t_shell *shell)
{
	t_token	*current;

	current = shell->token;
	while (current)
	{
		printf("Token: %s | Type: %d | State: | %d Variable: | %s\n",
			current->value, current->type, current->state, current->var_value);
		current = current->next;
	}
}

void	print_env(t_shell *shell)
{
	env_list	*current;

	current = shell->env;
	while (current)
	{
		printf("%s%s\n", current->key, current->value);
		current = current->next;
	}
}

void	print_exp(t_shell *shell)
{
	env_list	*current;

	current = shell->exp;
	while (current)
	{
		printf("declare -x %s\"%s\"\n", current->key, current->value);
		current = current->next;
	}
}
