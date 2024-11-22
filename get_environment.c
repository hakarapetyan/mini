#include "./include/minishell.h"

char	*get_the_key(char *str)
{
	char *key;
	int		i;

	key = NULL;
	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '=')
		i++;
	key = malloc(sizeof(char) * (i + 2));
	if (!key)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		key[i] = str[i];
		i++;
	}
	if (str[i])
		key[i++] = '=';
	//i++;
	key[i] = '\0';
	return (key);
}

char	*get_the_value(char *str)
{
	char *value;
	int	i;

	value = NULL;
	i = 0;
	if (!str || !ft_strchr(str, '='))
		return (NULL);
	while (*str)
		str++;
	while (*str != '=')
	{
		str--;
		i++;
	}
	value = malloc (sizeof(char) * (i + 1));
	if (!value)
		return (NULL);
	i = 0;
	while (str[i])
	{
		value[i] = str[i + 1];
		i++;
	}
	value[i] = '\0';
	return (value);
}

void	get_env_list(t_shell **shell, char *str)
{
	env_list *current;

	if (!str)
		return ;
	if (!(*shell) -> env)
	{
		(*shell) -> env = add_node(str);
	}
	else
	{
		 current = (*shell)->env;
        while (current -> next)
            current = current -> next;
        current -> next = add_node(str);
	}
}
void	get_exp_list(t_shell **shell, char *str)
{
	env_list *current;

	if (!str)
		return ;
	if (!(*shell) -> exp)
	{
		(*shell) -> exp = add_node(str);
	}
	else
	{
		 current = (*shell) -> exp;
        while (current -> next)
            current = current -> next;
        current -> next = add_node(str);
	}
}

void	get_environment(t_shell *shell, char **env)
{
	char **envir;
	int	i;

	i = 0;
	if (!(shell -> env))
	{
		while (env[i])
		{
			get_env_list(&shell, env[i]);
			i++;
		}
	}
	if (!(shell -> exp))
	{
		i = 0;
		while (env[i])
		{
			get_exp_list(&shell, env[i]);
			i++;
		}
		//free_args(envir);
	}
	//free_args(exp);
	// if (ft_strcmp(shell -> input, "env") == 0)
	// 		 print_env(shell);
	// if (ft_strcmp(shell -> input, "export") == 0)
	// 		print_exp(shell);
	// else if (ft_strcmp(shell -> input, "pwd") == 0)
	// 	my_pwd();
	// else if (ft_strcmp(shell -> input, "echo") == 0)
	// 	my_echo(4, shell -> input)
}

