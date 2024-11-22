/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakarape <hakarape@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:38:26 by hakarape          #+#    #+#             */
/*   Updated: 2024/11/22 21:38:53 by hakarape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	add_node_to_export(t_shell *shell, char **argv, int i)
{
	env_list	*exp;
	env_list	*tmp;

	exp = shell ->exp;
	if (!exp)
	{
		exp = add_node(argv[i]);
		return (1);
	}
	if (exp)
	{
		tmp = add_node(argv[i]);
		while (exp && exp->next)
			exp = exp->next;
		if (!check_key(shell->exp, tmp))
		{
			printf("add\n");
			exp ->next = add_node(argv[i]);
		}
		free_env(tmp);
	}
	return(0);
}
// int	add_node_to_env(t_shell *shell, char **argv, int i)
// {
// 	env_list	*exp;
// 	env_list	*tmp;

// 	env = shell ->env;
// 	if (!env)
// 	{
// 		env = add_node(argv[i]);
// 		return (1);
// 	}
// 	if (env)
// 	{
// 		tmp = add_node(argv[i]);
// 		while (env && env->next)
// 			env = env->next;
// 		if (!check_key(shell->env, tmp))
// 		{
// 			printf("add\n");
// 			env ->next = add_node(argv[i]);
// 		}
// 		free_env(tmp);
// 	}
// 	return(0);
// }
int check_key(env_list *list, env_list *new)
{
	while (list)
	{
		if (spec_strcmp(list->key, new->key) == 0)
			{
				list->value = ft_strdup(new->value);
				list->key =ft_strdup(new->key);
				return (1);
			}
		list=list->next;
	}
	return (0);
}
int my_export(int argc, char **arg, t_shell *shell)
{
	int	i;
	env_list *exp;
	i = 0;
	exp = shell -> exp;
	if (argc == 1)
		print_exp(shell);
	if (argc > 1)
	{
		if (arg[i] && ft_strcmp(arg[i], "export") == 0)
			i++;
		if (is_alpha(arg[i]) && my_strchr(arg[i], '_'))
		{
			write_print(arg[i], "minishell: export:", 2);
			ft_putendl_fd(" not a valid identifier", 2);
			write(2, "\n", 1);
			return (1);
		}
		add_node_to_export(shell, arg, i);
		return (0);
	}
}

int	execute_export(t_shell *shell)
{
	t_commands *cmd;

	cmd = shell -> command;

	if (cmd && ft_strcmp(cmd -> name, "export") == 0)
		if(my_export(shell -> token_count, cmd ->args, shell))
			return (1);
	return (0);
}