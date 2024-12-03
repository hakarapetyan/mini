// #include "../include/minishell.h"

// static void only_cd(t_shell *shell, char *tmp, char *cmd)
// {
// 	cmd = getcwd(NULL, 0);
// 	changes_in_list(shell->env, cmd, tmp);
// 	changes_in_list(shell->exp, cmd, tmp);
// }

// static int	cd_minus(t_shell *shell, char *cmd)
// {
// 	char *tmp;

// 	tmp = get_value(shell, "OLDPWD=");
// 	if (cd_errors_checking(tmp, "OLDPWD not set"))
// 		return (1);
// 	if (!tmp)
// 	{
// 		ft_putendl_fd("bash: cd: OLDPWD not set\n", 2);
// 		return(1);
// 	}
// 	changes_in_list(shell->env, tmp, cmd);
// 	changes_in_list(shell->exp, tmp, cmd);
// 	chdir(tmp);
// 	cmd = getcwd(NULL, 0);
// 	printf("%s\n", cmd);
// 	return (0);
// }

// static int my_cd_helper_norm(t_shell *shell, char *argv, char *tmp, char *cmd)
// {
// 			if (ft_strcmp(argv, "-") == 0)
// 			{
// 				if (cd_minus(shell, cmd))
// 					return (1);
// 			}
// 			else if (!chdir(argv))
// 				only_cd(shell, tmp, cmd);
// 			else
// 			{
// 				error_message(EXIT_FAILURE, argv);
// 				//simple_error(127, argv, )
// 				//printf("cd: %s: No such file or directory\n", argv);
// 				return(1);
// 			}
// 	return (0);
// }
// int	my_cd_helper(char *argv, t_shell *shell)//cd -
// {
// 	char	*cmd;
// 	char	*tmp;

// 	cmd = getcwd(NULL, 0);
// 	tmp = cmd;
// 	if (argv)
// 	{
// 		if (cmd != NULL)
// 		{
// 			if(my_cd_helper_norm(shell, argv, tmp, cmd))
// 				return (1);
// 			free(cmd);
// 		}
// 		else
// 		{
// 			error(ALLOCATION_ERR, shell);
// 			//ft_putendl_fd("path not found\n", 2);
// 			return(1);
// 		}
// 	}
// 	return (0);
// }


#include "../include/minishell.h"

static void update_env_lists(t_shell *shell, char *new_path, char *old_path)
{
    changes_in_list(shell->env, new_path, old_path);
    changes_in_list(shell->exp, new_path, old_path);
}

static int handle_cd_minus(t_shell *shell)
{
    char *oldpwd = get_value(shell, "OLDPWD=");
    char *current_path;

    if (cd_errors_checking(oldpwd, "OLDPWD not set"))
        return (1);
    if (!oldpwd)
    {
        ft_putendl_fd("minishell: cd: OLDPWD not set\n", 2);
        return (1);
    }
    if (chdir(oldpwd) != 0)
    {
        perror("chdir");
        return (1);
    }
    current_path = getcwd(NULL, 0);
    printf("%s\n", current_path);
    update_env_lists(shell, current_path, oldpwd);
    free(current_path);
    return (0);
}

static int handle_chdir(t_shell *shell, char *path)
{
    char *old_path = getcwd(NULL, 0);

    if (!old_path)
	{
		error(ALLOCATION_ERR, shell);
        return (0);
	}
    if (chdir(path) != 0)
    {
        error_message(EXIT_FAILURE, path);
        free(old_path);
        return (1);
    }
    char *new_path = getcwd(NULL, 0);
    update_env_lists(shell, new_path, old_path);
    free(old_path);
    free(new_path);
    return (0);
}

int my_cd_helper(char *argv, t_shell *shell)
{
    if (!argv || ft_strcmp(argv, "~") == 0)
        argv = get_value(shell, "HOME=");
    if (!argv)
    {
        ft_putendl_fd("minishell: cd: HOME not set\n", 2);
        return (1);
    }
    if (ft_strcmp(argv, "-") == 0)
        return handle_cd_minus(shell);
    return handle_chdir(shell, argv);
}
