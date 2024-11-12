/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakarape <hakarape@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:48:42 by hakarape          #+#    #+#             */
/*   Updated: 2024/11/12 12:40:08 by hakarape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	my_cd_helper(char **argv, int i, t_shell *shell)//cd -
{
	char	*cmd;
	char	*tmp;
	
	cmd = getcwd(NULL, 0);
	tmp = cmd;
	if (argv[i])
	{
		printf("argv%s\n", argv[i]);
		if (cmd != NULL)
		{
			if (ft_strcmp(argv[i], "-") == 0)
			{
				tmp = get_oldpwd(shell);
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
				printf("cd: %s: No suuuuch file or directory\n", argv[i]);
			free(cmd);
		}
		else
			printf("%s\n", "path not found");
	}
}

void	my_cd(int argc, char **argv, t_shell *shell)
{
	int	i;
	char	*oldpwd;
	char	*pwd;
	i = 0;
	oldpwd = get_pwd(shell);
	pwd = getenv("HOME");

	if (argc > 1)
	{
		if (argv[i] && (!ft_strcmp(argv[i], "cd")))
			i++;
		my_cd_helper(argv, i, shell);
	}
	else
	{
		chdir(pwd);
		change_oldpwd(shell, pwd, oldpwd);
		// must be changed ENV
	}
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
void	execute_cd(t_shell *shell)
{
	t_commands *cmd;

	cmd = shell -> command;

	if (cmd && ft_strcmp(cmd -> name, "cd") == 0)
		my_cd(shell -> token_count, cmd -> args, shell);
}
