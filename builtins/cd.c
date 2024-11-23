/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakarape <hakarape@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:48:42 by hakarape          #+#    #+#             */
/*   Updated: 2024/11/23 16:46:46 by hakarape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	cd_errors_checking(char *oldpwd, char *home)
{
	if (!oldpwd)
	{
		ft_putendl_fd("bash: cd: OLDPWD not set\n", 2);
		return(1);
	}
	if (!home)
	{
		ft_putendl_fd("bash: cd: HOME not set\n", 2);
		return(1);
	}
	return (0);
}
int	my_cd_helper(char **argv, int i, t_shell *shell)//cd -
{
	char	*cmd;
	char	*tmp;
	
	cmd = getcwd(NULL, 0);
	tmp = cmd;
	if (argv[i])
	{
		if (cmd != NULL)
		{
			if (ft_strcmp(argv[i], "-") == 0)
			{
				tmp = get_value(shell, "OLDPWD=");
				if (!tmp)
				{
					ft_putendl_fd("bash: cd: OLDPWD not set\n", 2);
					return(1);
				}
				changes_in_list(shell->env, tmp, cmd);
				changes_in_list(shell->exp, tmp, cmd);
				chdir(tmp);
				cmd = getcwd(NULL, 0);
				printf("%s\n", cmd);
			}
			else if (!chdir(argv[i]))
			{
				cmd = getcwd(NULL, 0);
				changes_in_list(shell->env, cmd, tmp);
				changes_in_list(shell->exp, cmd, tmp);
			}
			else
			{ 
				printf("cd: %s: No such file or directory\n", argv[i]);
				return(1);
			}
			free(cmd);
		}
		else
		{
			printf("%s\n", "path not found");
			return(1);
		}
	}
	return (0);
}

int	my_cd(int argc, char **argv, t_shell *shell)
{
	int	i;
	char	*oldpwd;
	char	*home;
	
	i = 0;
	oldpwd = get_value(shell, "PWD=");
	home = get_value(shell, "HOME=");

	if (cd_errors_checking(oldpwd, home))
		return (1);
	if (argc > 1)
	{
		if (argv[i] && (!ft_strcmp(argv[i], "cd")))
			i++;
		if (my_cd_helper(argv, i, shell))
			return (1);
	}
	else
	{
		chdir(home);
		changes_in_list(shell->env, home, oldpwd);
		changes_in_list(shell->exp, home, oldpwd);
	}
	return (0);
}
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
	while (env)
	{
		if (ft_strcmp(env ->key, key) == 0)
			return (env ->value);
		env = env->next;
	}
	return (NULL);
}
int	execute_cd(t_shell *shell)
{
	t_commands *cmd;

	cmd = shell -> command;
	if (cmd && ft_strcmp(cmd -> name, "cd") == 0)
		if (my_cd(shell -> token_count, cmd -> args, shell))
			return (1);
		return (0);
}
// void changes_in_exp(t_shell *shell, char *pwd,char *oldpwd)
// {
// 	env_list *exp;
	
// 	exp = shell -> exp;
// 	while (exp)
// 	{
// 		if (ft_strcmp(exp ->key, "OLDPWD=") == 0)
// 		{
// 			exp -> value = ft_strdup(oldpwd);
// 		}
// 		else if (ft_strcmp(exp ->key, "PWD=") == 0)
// 		{	
// 			exp -> value = ft_strdup(pwd);
// 		}
// 		exp = exp -> next;	
// 	}
// }
// char *get_oldpwd(t_shell *shell)
// {
// 	env_list *env;
	
// 	env = shell -> env;
// 	while (env)
// 	{
// 		if (ft_strcmp(env ->key, "OLDPWD=") == 0)
// 			return (env ->value);
// 		env = env->next;
// 	}
// 	return (NULL);
// }
// char *get_pwd(t_shell *shell)
// {
// 	env_list *env;
	
// 	env = shell -> env;
// 	while (env)
// 	{
// 		if (ft_strcmp(env ->key, "PWD=") == 0)
// 			return (env ->value);
// 		env = env->next;
// 	}
// 	return (NULL);
// }
