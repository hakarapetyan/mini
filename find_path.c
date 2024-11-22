#include "./include/minishell.h"

static void free_path(char ***arr)
{

    int i = 0;

    if (arr == NULL || *arr == NULL)
        return;

    while ((*arr)[i])
    {
        free((*arr)[i]);
        (*arr)[i] = NULL;
        i++;
    }
    free(*arr);
    *arr = NULL;
}

char	**find_path_from_env(t_shell *shell)
{
	char		**path;
	char	*key;

	key = NULL;
	path = NULL;

	if (!(shell -> env))
		return (NULL);
	key = is_key(shell -> env, "PATH");
	if (!key)
		return (NULL);
	path = ft_split(key, ':');
	return (path);
}

char	*find_path(t_shell *shell, char	*command_name)
{
	char	**path;
	char	*tmp;
	char	*tmp2;
	int		i;

	i = 0;
	path = find_path_from_env(shell);
	if (!path)
		return (NULL);
	while (path[i])
	{
		tmp = another_strjoin(path[i], "/");
		tmp2 = ft_strjoin(tmp,command_name);
		if (access(tmp2,X_OK || F_OK) == 0)
		{
			free_path(&path);
			return (tmp2);
		}
		i++;
		free_arr(&tmp2);
	}
	free_path(&path);
	return (NULL);
}
