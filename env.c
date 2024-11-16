/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakarape <hakarape@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 14:14:20 by hakarape          #+#    #+#             */
/*   Updated: 2024/11/16 17:03:28 by hakarape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	my_env_helper(t_shell *shell, char **argv, int i)
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
int my_env(int argc,t_shell *shell, char **argv)
{
	int	i;

	i = 0;
	if (argc == 1)
		 print_env(shell);
	if (argc > 1)
	{
		if (argv[i] && (!ft_strcmp(argv[i], "env")))
			i++;
		if (my_env_helper(shell, argv, i))
			return (1);
	}
	return (0);
}
void	execute_env(t_shell *shell)
{
	t_commands *cmd;
	int i=0;

	cmd = shell -> command;
	if (cmd && ft_strcmp(cmd -> name, "env") == 0)
		my_env(shell -> token_count, shell, cmd->args);
}