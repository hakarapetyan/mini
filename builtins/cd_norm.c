/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_norm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakarape <hakarape@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:32:45 by hakarape          #+#    #+#             */
/*   Updated: 2024/12/05 14:32:45 by hakarape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int  only_cd(t_shell *shell)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd != NULL)
	{
		changes_in_list(shell->env, pwd, "PWD=");
		changes_in_list(shell->exp, pwd, "PWD=");
	}
	else
	{
		free_str(pwd);
		return (1);
	}
	free_str(pwd);
	return (0);
}
static int	cd_minus(t_shell *shell)
{
	char *oldpwd;
	char *pwd;

	oldpwd = get_value(shell, "OLDPWD=");
	pwd = get_value(shell, "PWD=");
	if (!pwd && oldpwd && ft_strcmp(oldpwd, "\0") != 0)
	{
		chdir(oldpwd);
		printf("%s\n", oldpwd);
		return (0);
	}
	if (oldpwd && pwd)
	{
		chdir(oldpwd);
		changes_in_list(shell->env, oldpwd, "PWD=");
		changes_in_list(shell->exp, oldpwd, "PWD=");
		printf("%s\n", oldpwd);
	}
	else
		simple_error(EXIT_FAILURE, "cd", "OLDPWD not set");
	return (0);
}

static int my_cd_helper_norm(t_shell *shell, char *argv)
{
			if (ft_strcmp(argv, "-") == 0)
			{
				if (cd_minus(shell))
					return (1);
			}
			else if (!chdir(argv))
			{
				if(only_cd(shell))
				{
					// pwd_error(shell);
					error(GET_CWD_ERROR, shell);
					return (1);
				}
			}
			else
			{
				another_simple_error(EXIT_FAILURE, "cd: ", argv, "No such file or directory");
				return(1);
			}
	return (0);
}
int	my_cd_helper(char *argv, t_shell *shell)//en apushutyuny
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (argv)
	{
		if (oldpwd != NULL)
		{
			if(my_cd_helper_norm(shell, argv))
			{
				free_str(oldpwd);
				return (1);
			}
		}
		else
		{
			// pwd_error(shell);
			printf("hihio\n");
			error(GET_CWD_ERROR, shell);
			free_str(oldpwd);
			return(1);
		}
	}
	free_str(oldpwd);
	return (0);
}

