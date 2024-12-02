#include "../include/minishell.h"

static void only_cd(t_shell *shell, char *tmp, char *cmd)
{
	cmd = getcwd(NULL, 0);
	changes_in_list(shell->env, cmd, tmp);
	changes_in_list(shell->exp, cmd, tmp);
}

static int	cd_minus(t_shell *shell, char *cmd)
{
	char *tmp;

	tmp = get_value(shell, "OLDPWD=");
	if (cd_errors_checking(tmp, "OLDPWD not set"))
		return (1);
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
	return (0);
}

static int my_cd_helper_norm(t_shell *shell, char *argv, char *tmp, char *cmd)
{
			if (ft_strcmp(argv, "-") == 0)
			{
				if (cd_minus(shell, cmd))
					return (1);
			}
			else if (!chdir(argv))
				only_cd(shell, tmp, cmd);
			else
			{
				error_message(EXIT_FAILURE, argv);
				//simple_error(127, argv, )
				//printf("cd: %s: No such file or directory\n", argv);
				return(1);
			}
	return (0);
}
int	my_cd_helper(char *argv, t_shell *shell)//cd -
{
	char	*cmd;
	char	*tmp;

	cmd = getcwd(NULL, 0);
	tmp = cmd;
	if (argv)
	{
		if (cmd != NULL)
		{
			if(my_cd_helper_norm(shell, argv, tmp, cmd))
				return (1);
			free(cmd);
		}
		else
		{
			error(ALLOCATION_ERR, shell);
			//ft_putendl_fd("path not found\n", 2);
			return(1);
		}
	}
	return (0);
}
