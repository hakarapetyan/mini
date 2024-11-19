/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakarape <hakarape@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 20:18:16 by hakarape          #+#    #+#             */
/*   Updated: 2024/11/19 16:22:24 by hakarape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int	del_one(env_list *env)
{
	if (!(env))
		return (1);
	free(env->value);
	free(env->key);
	free(env);
	return (0);	
}
int del_from_lst(env_list *env, char *nv)
{
	env_list *temp;
	if (!env)
		return (1);
	if (env->next)
	{
		while (env -> next)
		{
			if (spec_strcmp(env->next->key, nv) == 0)
			{
				temp = env->next;
				env->next = env->next->next;
				del_one(temp);
				return (1);
			}
			env = env ->next;
		}
	}
	if (!env ->next && spec_strcmp(env->key, nv) == 0)
	{
		del_one(env);
		free(env);
		return (1);
	}
	return (0);
}
int my_unset(int size, char **arg, t_shell *shell)
{
	int	i;
	env_list	*env;
	env_list	*exp;

	i = 0;
	env = shell ->env;
	exp = shell ->exp;
	if (arg[i] && ft_strcmp(arg[i], "unset") == 0)
		i++;
	if (is_alpha(arg[i]) && my_strchr(arg[i], '?') && my_strchr(arg[i], '_'))
	{
		write_print(arg[i], "minishell: unset:", 2);
		ft_putendl_fd(" not a valid identifier", 2);
		write(2, "\n", 1);
	}
	while (arg[i])
	{
		if (del_from_lst(env, arg[i]))
		{
			del_from_lst(exp, arg[i]);
			return (1);
		}
		i++;
	}
	return (0);
}
void	execute_unset(t_shell *shell)
{
	t_commands *cmd;

	cmd = shell -> command;

	if (cmd && ft_strcmp(cmd -> name, "unset") == 0)
		my_unset(shell -> token_count, cmd -> args, shell);
}
void write_print(char *arg, char * msg, int fd)
{
	ft_putendl_fd(msg, 2);
	write(2, "`", 1);
	ft_putendl_fd(arg, 2);
	write(2, "'", 1);
}