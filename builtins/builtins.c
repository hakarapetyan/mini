/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakarape <hakarape@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 14:12:09 by hakarape          #+#    #+#             */
/*   Updated: 2024/11/23 16:19:15 by hakarape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	builtins(t_shell *shell)
{
	if (execute_pwd(shell))
		return (1);
	else if (execute_env(shell))
		return (1);
	else if (execute_export(shell))
		return (1);
	else if (execute_unset(shell))
		return (1);
	else if (execute_cd(shell))
		return (1);
	return (0);
}