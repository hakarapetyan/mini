/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 20:18:16 by hakarape          #+#    #+#             */
/*   Updated: 2024/12/14 17:24:17 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
				return (0);
			}
			env = env ->next;
		}
	}
	if (!env ->next && spec_strcmp(env->key, nv) == 0)
	{
		del_one(env);
		free(env);
		return (0);
	}
	return (0);
}
int my_unset_helper(char **arg, env_list *env, env_list *exp)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] && ft_strcmp(arg[i], "unset") == 0)
			i++;
		if (!is_alpha(arg[i]) /*|| !my_strchr(arg[i], '_')*/)
		{
			another_simple_error(EXIT_FAILURE, "unset: ", arg[1], "numeric argument required");
			// simple_error(EXIT_FAILURE, arg[i],"not a valid identifier");
			// write_print(arg[i], "minishell: export:", 2);
			// ft_putendl_fd(" not a valid identifier", 2);
			// write(2, "\n", 1);
			return (1);
		}
		if (!del_from_lst(env, arg[i]))
			del_from_lst(exp, arg[i]);
		else
			return (1);
		i++;
	}
	return (0);
}
int my_unset(int size, char **arg, t_shell *shell)
{
	env_list	*env;
	env_list	*exp;

	env = shell ->env;
	exp = shell ->exp;
	if (size == 1)
		return (1);
	if (my_unset_helper(arg, env, exp))
		return (1);
	return (0);
}
// int	execute_unset(t_shell *shell)
// {
// 	t_commands *cmd;

// 	cmd = shell -> command;

// 	if (cmd && ft_strcmp(cmd -> name, "unset") == 0)
// 		if(my_unset(shell -> token_count, cmd -> args, shell))
// 			return(1);
// 		return(0);
// }
