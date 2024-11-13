/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakarape <hakarape@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 20:18:16 by hakarape          #+#    #+#             */
/*   Updated: 2024/11/13 21:26:11 by hakarape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	my_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	// if (c == '\0')
	// 	return (1);
	while (s[i])
	{
		if (s[i] == c)
			return (0);
		i++;
	}
	return (1);
}
void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}
int is_alpha(char *arg)
{
    int i;
    
    i = 0;
    if (arg[i] == '+' || arg[i] == '-')
		i++;
    while (arg[i])
    {
        if ((arg[i] >= 65 && arg[i] <= 90) || (arg[i] >= 97 && arg[i] <= 122))
            i++;
        else
        return (1);
    }
    return (0);
}
int is_digit_unset(char *arg)
{
    int i;
    
    i = 0;
    if (arg[i] == '+' || arg[i] == '-')
		i++;
    while (arg[i])
    {
        if (arg[i] >= 48 && arg[i] <= 57)
            i++;
        else
        return (1);
    }
    return (0);
}

void my_unset(int size, char **arg, t_shell *shell)
{
	int	i;

	i = 0;
	if (is_alpha(arg[i]) && ft_strchr(arg[i], '?') && ft_strchr(arg[i], '_'))
		ft_putendl_fd("minishell: unset: `': not a valid identifier", 2);
		
	
}
int	del_one(env_list env)
{
	if (!(*env))
		return (1);
	free(env.value);
	free(env.key);
	//free(env);
	return (0);	
}
int del_from_lst(env_list *env, env_list nv)
{
	if (!env)
		return (1);
	if (!env ->next)
	{
		del_one(*env);
		free(env);
	}
	while (env -> next)
	{
		if (env->next->key == nv.key)
		{
			env->next = env->next->next;
			del_one(env->next);
			free(env);
		}
		env = env ->next;
	}
	
}

void	execute_unset(t_shell *shell)
{
	t_commands *cmd;

	cmd = shell -> command;

	if (cmd && ft_strcmp(cmd -> name, "unset") == 0)
		my_unset(shell -> token_count, cmd -> args, shell);
}