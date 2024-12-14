/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:33:10 by hakarape          #+#    #+#             */
/*   Updated: 2024/12/14 16:17:39 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

void	print_env(t_shell *shell)
{
	env_list	*current;

	current = shell->env;
	if (!current)
		return ;
	while (current)
	{
		printf("%s%s\n", current->key, current->value);
		current = current->next;
	}
}

void	print_exp(t_shell *shell)
{
	int	i;
	char	**envir;

	i = 0;
	envir = sorting_for_export(shell ->exp);
	while (envir[i])
	{
		print_exp_helper(envir[i]);
		i++;
	}
	free_args(envir);
}
void	print_exp_helper(char *exp)
{
	int	i;

	i = 0;
	if(ft_strchr(exp, '='))
	{
		printf("declare -x ");
		while(*exp && *exp != '=')
		{
			printf("%c", *exp);
			exp++;
		}
		printf("%c", *exp);
		if (*exp)
		{
			exp++;
			printf("\"%s\"\n", exp);
		}
	}
	else
		printf("declare -x %s\n", exp);
}
