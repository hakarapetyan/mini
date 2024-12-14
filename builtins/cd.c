/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:48:42 by hakarape          #+#    #+#             */
/*   Updated: 2024/12/14 16:16:29 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
static int check_oldpwd(env_list *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}
static void  add_oldpwd_to_env(env_list *list, char *pwd, t_shell *shell)
{
	// if (!list || (*pwd))
	// 	return ;
	env_list *tmp = list;
	if (!check_oldpwd(tmp, "OLDPWD="))
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
	// if	(argc > 2)
	// {
	// 	ft_putendl_fd("minishell: cd: too many arguments\n", 2);
	// 	return (1);
	// }
	if (argv[i] && (!ft_strcmp(argv[i], "cd")))
		i++;
	if (my_cd_helper(argv[i], shell))
		return (1);
	return (0);
}
int	my_cd(int argc, char **argv, t_shell *shell)
{
	char	*pwd;
	char	*home;

	env_list *env=shell->env;
	env_list *exp = shell->exp;
	pwd = get_value(shell, "PWD=");
	//oldpwd = get_value(shell, "OLDPWD=");
	if (shell -> flag != 1)
	{
		add_oldpwd_to_env(env, pwd, shell);//shell taluc segv
		add_oldpwd_to_exp(exp, pwd, shell);
	}
	home = get_value(shell, "HOME=");
	if (argc > 1)
	{
		if(my_cd_norm( argv, shell))
			return(1);
	}
	// if (cd_errors_checking(oldpwd, "OLDPWD not set"))
	// 	return (1);
	else
	{
		chdir(home);
		changes_in_list(shell->env, home, pwd);
		changes_in_list(shell->exp, home, pwd);
	}
	return (0);
}

