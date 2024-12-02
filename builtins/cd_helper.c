#include "../include/minishell.h"

void changes_in_list(env_list *list, char *pwd,char *oldpwd)
{
	while (list)
	{
		if (ft_strcmp(list ->key, "OLDPWD=") == 0)
		{
			list -> value = ft_strdup(oldpwd);
		}
		else if (ft_strcmp(list ->key, "PWD=") == 0)
		{	
			list -> value = ft_strdup(pwd);
		}
		list = list -> next;	
	}
}
char *get_value(t_shell *shell, char *key)
{
	env_list *env;
	
	env = shell -> env;
	if (!(*key) || !key)
		return (NULL);
	while (env)
	{
		if (ft_strcmp(env ->key, key) == 0)
		{
			if (!env->value)
				return(NULL);
			return (env ->value);
		}
		env = env->next;
	}
	return (NULL);
}
