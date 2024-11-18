/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakarape <hakarape@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:38:26 by hakarape          #+#    #+#             */
/*   Updated: 2024/11/18 14:46:27 by hakarape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	my_export_helper(t_shell *shell, char **argv, int i)
{
	env_list	*env;

	env = shell ->env;
	if (!env)
	{
		env = add_node(argv[i]);
		return (1);
	}
	if (env->next)
		while (env->next)
			env = env->next;
	env ->next = add_node(argv[i]);
	return(0);
}
int my_export(int argc, char **arg, t_shell *shell)
{
	int	i;

	i = 0;
	if (argc == 1)
		print_exp(shell);
	if (argc > 1)
	{
	if (arg[i] && ft_strcmp(arg[i], "export") == 0)
		i++;
	if (is_alpha(arg[i]) && my_strchr(arg[i], '?') && my_strchr(arg[i], '_'))
	{
		write_print(arg[i], "minishell: export:", 2);
		ft_putendl_fd(" not a valid identifier", 2);
		write(2, "\n", 1);
		return (1);
	}
	else
		my_export_helper(shell, arg, i);
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