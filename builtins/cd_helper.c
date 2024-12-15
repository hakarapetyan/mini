/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakarape <hakarape@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:32:36 by hakarape          #+#    #+#             */
/*   Updated: 2024/12/05 14:32:36 by hakarape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void changes_in_list(env_list *list, char *pwd, const char *key)
{
	while (list)
	{
		// if (ft_strcmp(list ->key, "OLDPWD=") == 0)
		// {
		// 	list -> value = ft_strdup(oldpwd);
		// }
		if (ft_strcmp(list ->key, key) == 0)
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

void pwd_error(t_shell *shell)
{
	env_list *env;
	char *pwd;
	char *oldpwd;

	env = shell->env;
	pwd = get_value(shell, "PWD=");
	oldpwd=get_value(shell,"OLDPWD=");
	pwd=ft_strjoin(pwd, "/..");
	printf("pwd=%s\n", pwd);
	chdir("/..");
	char *new=getcwd(NULL,0);
	printf("new=%s\n", new);
	changes_in_list(env, pwd, "PWD=");
	free(pwd);
	// printf("pwd=%s\n", pwd);
	// printf("oldpwd=%s\n", oldpwd);
}
