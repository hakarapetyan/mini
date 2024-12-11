
// Increment SHLVL
char *inc_shlvl(t_shell *shell)
{
    char *value;
    int atoi;
    char *itoa;

    value = get_value(shell, "SHLVL=");
    printf("value=%s\n", value);
    atoi = ft_atoi(value);
    itoa = ft_itoa(atoi + 1);
    return itoa;
}

// Change SHLVL
int check_key(env_list *list, const char *key)
{
	env_list *env;

	env = list;
    if (ft_strcmp(env->key, key) == 0)
        return (1);
    env = env->next;
	return (0);
}

void chang_shlvl(t_shell *shell)
{
	env_list *list;
	char	*shlvl;

	shlvl = inc_shlvl(shell);
	list = shell->env;
	if (!ft_strcmp(shell -> input, "./minishell"))
	{
		while(list)
		{
			if (check_key(list, "SHLVL=") == 1)
			{
				free(list->value);
				list->value=ft_strdup(shlvl);
				free(shlvl);
				return;
			}
			list = list->next;
		}
	}

	free(shlvl);
	return ;
}
