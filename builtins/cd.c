/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakarape <hakarape@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:48:42 by hakarape          #+#    #+#             */
/*   Updated: 2024/12/17 12:00:32 by hakarape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
int check_key(env_list *list, char *key)
{
	env_list *env;

	env = list;
	if (env)
	{
		while (env)
		{
			if (spec_strcmp(env->key, key) == 0)
				return (1);
			env = env->next;
		}
	}
	return (0);
}
static void  add_oldpwd_to_env(env_list *list, char *pwd, t_shell *shell)
{
	// if (!list || (*pwd))
	// 	return ;
	env_list *tmp = list;
	if (!check_key(tmp, "OLDPWD="))
	{
		shell->flag = 1;
		add_node_to_list(list, "OLDPWD=");
		while (list -> next)
			list = list->next;
		if (ft_strcmp(list->value, "\0") == 0)
			list->value = ft_strdup(pwd);
	}
}

static void add_oldpwd_to_exp(env_list *list, char *pwd, t_shell *shell)
{
	// if (!list || *pwd)
	// 	return ;
		while (list -> next)
		{
			if (ft_strcmp(list->key, "OLDPWD") == 0 /*&& ft_strcmp(list->value, "\0") == 0*/)
				{
					list->key = ft_strdup("OLDPWD=");
					list->value = ft_strdup(pwd);
					shell->flag = 1;
				}
			list = list->next;
		}
}

int	cd_errors_checking(char *oldpwd, char *home)
{
	if (!oldpwd)
	{
		simple_error(EXIT_FAILURE, "cd", home);
		//ft_putendl_fd("bash: cd: OLDPWD not set\n", 2);
		return(1);
	}
	return (0);
}

static int	my_cd_norm(char **argv, t_shell *shell)
{
	int i;

	i = 0;
	if (argv[i] && (!ft_strcmp(argv[i], "cd")))
		i++;
	if (my_cd_helper(argv[i], shell))
		return (1);
	return (0);
}
static void list_changes(env_list *list, char *pwd, char *oldpwd)
{
	while (list)
	{
		if (ft_strcmp(list ->key, "OLDPWD=") == 0)
		{
			list -> value = ft_strdup(oldpwd);
		}
		if (ft_strcmp(list ->key, "PWD=") == 0)
		{	
			list -> value = ft_strdup(pwd);
		}
		list = list -> next;	
	}
}
static int list_changes_norm(t_shell *shell, char *pwd)
{
	char *new;
	env_list *env;
	env_list *exp;

	env = shell->env;
	exp = shell->exp;
	new = getcwd(NULL, 0);
	if (shell -> flag != 1 && ft_strcmp(pwd, new) != 0)
	{
		add_oldpwd_to_env(env, pwd, shell);
		add_oldpwd_to_exp(exp, pwd, shell);
	}
	else if (ft_strcmp(pwd, new) != 0)
	{
		changes_in_list(shell->env, pwd, "OLDPWD=");
		changes_in_list(shell->exp, pwd, "OLDPWD=");
	}
	return (0);
}
int	my_cd(int argc, char **argv, t_shell *shell)
{
	char	*pwd;
	char	*home;
	
	// env_list *env=shell->env;
	// env_list *exp = shell->exp;
	pwd = get_value(shell, "PWD=");
	home = get_value(shell, "HOME=");
	if (argc > 1)
	{
		if(my_cd_norm( argv, shell))
			return(1);
	}
	if (argc == 1)
	{
		if(!chdir(home))
		{
			list_changes(shell->env, home, pwd);
			list_changes(shell->exp, home, pwd);
			// changes_in_list(shell->env, home, "PWD=");
			// changes_in_list(shell->exp, home, "PWD=");
			// changes_in_list(shell->env, pwd, "OLDPWD=");
			// changes_in_list(shell->exp, pwd, "OLDPWD=");
		}
		else
			simple_error(EXIT_FAILURE, "cd", "HOME not set");		
	}
	list_changes_norm(shell, pwd);
	// new = getcwd(NULL, 0);
	// if (shell -> flag != 1 && ft_strcmp(pwd, new) != 0)
	// {
	// 	add_oldpwd_to_env(env, pwd, shell);
	// 	add_oldpwd_to_exp(exp, pwd, shell);
	// }
	// else if (ft_strcmp(pwd, new) != 0)
	// {
	// 	changes_in_list(shell->env, pwd, "OLDPWD=");
	// 	changes_in_list(shell->exp, pwd, "OLDPWD=");
	// }	
	return (0);
}