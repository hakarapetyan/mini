/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakarape <hakarape@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:33:23 by hakarape          #+#    #+#             */
/*   Updated: 2024/12/18 20:04:29 by hakarape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	add_node_to_list(env_list *list, char *argv)
{
	env_list	*tmp;
	env_list	*cmp;

	cmp = list;
	if (!list)
	{
		list = add_node(argv);
		return (1);
	}
	if (list)
	{
		tmp = add_node(argv);
		while (list && list->next)
			list = list->next;
		if (!check_two_keys(cmp, tmp))
			list ->next = add_node(argv);
		free_env(tmp);
	}
	return(0);
}

int check_two_keys(env_list *list, env_list *new)
{
	while (list)
	{
		if (spec_strcmp(list->key, new->key) == 0)
			{
				free_str(list -> value);
				free_str(list -> key);
				list->value = ft_strdup(new->value);
				list->key = ft_strdup(new->key);
				return (1);
			}
		list=list->next;
	}
	return (0);
}
static	int	ft_isalpha(int c)
{
	if ((c < 65 || c > 90) && (c < 97 || c > 122))
		return (0);
	return (1);
}
int	my_isalnum(int c)
{
	if (ft_isalpha(c) || (c >= 48 && c <= 57))
		return (1);
	return (0);
}
int	my_export_helper(char **arg, env_list *env, env_list *exp)
{
	int	i;

	i = 0;
	if (arg[i] && ft_strcmp(arg[i], "export") == 0)
			i++;
		while (arg[i])
		{
			if (!is_alpha(arg[i]) /*|| !my_strchr(arg[i], '_')*/)
			{
				another_simple_error(EXIT_FAILURE, "export: ", arg[1], "not a valid identifier");
				//simple_error(EXIT_FAILURE, arg[i],"not a valid identifier");
				// write_print(arg[i], "minishell: export:", 2);
				// ft_putendl_fd(" not a valid identifier", 2);
				// write(2, "\n", 1);
				return (1);
			}
			add_node_to_list(exp, arg[i]);
			if (ft_strchr(arg[i], '='))
				add_node_to_list(env, arg[i]);
			i++;
		}
		return (0);
}
int my_export(int argc, char **arg, t_shell *shell)
{
	env_list *exp;
	env_list *env;

	exp = shell -> exp;
	env = shell->env;

	if (argc == 1)
		print_exp(shell);
	if (argc > 1)
		if (my_export_helper(arg,env,exp))
			return(1);
	return(0);
}
