/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakarape <hakarape@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:48:42 by hakarape          #+#    #+#             */
/*   Updated: 2024/11/14 21:36:09 by hakarape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

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
				tmp = get_oldpwd(shell);
				if (!tmp)
				{
					ft_putendl_fd("bash: cd: OLDPWD not set\n", 2);
					return(1);
				}
				change_oldpwd(shell, tmp, cmd);
				chdir(tmp);
				cmd = getcwd(NULL, 0);
				printf("%s\n", cmd);
			}
			else if (!chdir(argv[i]))
			{
				cmd = getcwd(NULL, 0);
				change_oldpwd(shell, cmd, tmp);
			}
			else
			{ 
				printf("cd: %s: No suuuuch file or directory\n", argv[i]);
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
	char	*pwd;
	i = 0;
	oldpwd = get_pwd(shell);
	pwd = get_home(shell);

	if (!oldpwd)
	{
		ft_putendl_fd("bash: cd: OLDPWD not set\n", 2);
		return(1);
	}
	if (!pwd)
	{
		ft_putendl_fd("bash: cd: HOME not set\n", 2);
		return(1);
	}
	if (argc > 1)
	{
		if (argv[i] && (!ft_strcmp(argv[i], "cd")))
			i++;
		if (my_cd_helper(argv, i, shell))
			return (1);
	}
	else
	{
		chdir(pwd);
		change_oldpwd(shell, pwd, oldpwd);
		// must be changed ENV
	}
	return (0);
}
void change_oldpwd(t_shell *shell, char *pwd,char *oldpwd)
{
	env_list *env;
	
	env = shell -> env;
	(void)pwd;
	while (env)
	{
		if (ft_strcmp(env ->key, "OLDPWD=") == 0)
		{
			env -> value = ft_strdup(oldpwd);
		}
		else if (ft_strcmp(env ->key, "PWD=") == 0)
		{	
			env -> value = ft_strdup(pwd);
		}
		env = env -> next;	
	}
}
char *get_oldpwd(t_shell *shell)
{
	env_list *env;
	
	env = shell -> env;
	while (env)
	{
		if (ft_strcmp(env ->key, "OLDPWD=") == 0)
			return (env ->value);
		env = env->next;
	}
	return (NULL);
}
char *get_pwd(t_shell *shell)
{
	env_list *env;
	
	env = shell -> env;
	while (env)
	{
		if (ft_strcmp(env ->key, "PWD=") == 0)
			return (env ->value);
		env = env->next;
	}
	return (NULL);
}
char *get_home(t_shell *shell)
{
	env_list *env;
	
	env = shell -> env;
	while (env)
	{
		if (ft_strcmp(env ->key, "HOME=") == 0)
			return (env ->value);
		env = env->next;
	}
	return (NULL);
}
void	execute_cd(t_shell *shell)
{
	t_commands *cmd;

	cmd = shell -> command;

	if (cmd && ft_strcmp(cmd -> name, "cd") == 0)
		my_cd(shell -> token_count, cmd -> args, shell);
}
