#include "./include/minishell.h"


static void	create_first_command(t_token **tkn, t_commands **tmp, t_shell *shell)
 {
	*tmp = create_command((*tkn) -> value, tkn);
	shell -> command = *tmp;
	if (!(shell -> command))
		error(ALLOCATION_ERR, shell);
	shell -> command_count++;
}

void	create_commands(t_shell *shell)
{
	t_token		*tkn;
	t_commands	*tmp;

	// if (!shell -> token)
	// 	error(ALLOCATION_ERR, shell);
	tmp = shell -> command;
	tkn = shell -> token;
	if (tkn)
	{
		while (tkn)
		{
			if (!tmp)
				create_first_command(&tkn, &tmp, shell);
			else
				add_command(&tkn, &tmp, shell);
			get_args(&tkn, shell);
		}
	}
}




static void	get_redir_helper(t_token **token,  t_shell *shell, char **type)
{
	if (*type)
		free(*type);
	if (*token && (*token) -> next)
		*type = ft_strdup((*token) -> next -> value);
	if (!(*type))
		error(ALLOCATION_ERR, shell);

//	open_the_file(shell, (*type));
}




static void	get_redir(t_token **token,t_commands **tmp,  t_shell *shell)
{
	if ((*token) -> type == R_IN)
		get_redir_helper(token, shell, &((*tmp) -> r_in));
	else if ((*token) -> type == R_OUT)
		get_redir_helper(token, shell, &((*tmp) -> r_out));
	else if ((*token) -> type == R_APPEND)
	{
		get_redir_helper(token, shell, &((*tmp) -> r_out));
		(*tmp) -> is_append = 1;
	}
	else if ((*token) -> type == R_HEREDOC)
	{
		get_redir_helper(token, shell, &((*tmp) -> r_in));
		(*tmp) -> is_heredoc = 1;
	}
	(*token) = (*token)->next ? (*token)->next->next : NULL;
}


void	add_args(t_token **token,t_commands **tmp,  t_shell *shell)
{
	int	i;

	i = 0;
	while ((*token) && (*token) -> type != PIPE)
	{
		if (is_redirection((*token) -> type))
			get_redir(token, tmp, shell);
		if ((*token) && (!is_redirection((*token) -> type) && (*token) -> type != PIPE))
		{
			if ((*token) -> var_value)
				(*tmp) -> args[i] = ft_strdup(((*token)) -> var_value);
			else
				(*tmp) -> args[i] = ft_strdup(((*token)) -> value);
			if (!(*tmp) -> args[i])
				error(ALLOCATION_ERR, shell);
			(*token) = (*token) -> next;
			i++;
		}
	}
	(*tmp) -> name = ft_strdup((*tmp) -> args[0]);
	if ((*tmp) -> args)
		(*tmp) -> args[i] = NULL;
	(*tmp) = (*tmp) -> next;

}


void get_args(t_token **token, t_shell *shell)
{
	t_commands	*tmp;

	tmp = shell -> command;
    if (!token || !*token || !shell || !shell->token)
        return;
	if (!tmp)
		return ;
	while (tmp -> next)
		tmp = tmp -> next;
	if (tmp -> args)
		return ;
	tmp -> args = malloc(sizeof(char *) * (args_count(token) + 1));
	if (!tmp -> args)
		error(ALLOCATION_ERR, shell);
	add_args(token,&tmp, shell);
}

void	add_command(t_token **tkn, t_commands **tmp, t_shell *shell)
{
	if (!ft_strcmp((*tkn) -> value, "|"))
	{
			while ((*tmp) -> next)
				(*tmp) = (*tmp) -> next;
			(*tmp) -> next = create_command((*tkn) -> next -> value, NULL);
			if (!((*tmp) -> next))
				free_shell(shell);
			(*tmp) -> next -> prev = *tmp;
			(*tkn) = (*tkn) -> next;
			(*tmp) = (*tmp) -> next;
			shell -> command_count++;
	}
}

static void	create_command_helper(t_token **tkn, t_commands **command)
{
	if (tkn && is_redirection((*tkn) -> type))
	{
		if (is_redirection((*tkn) -> type))
		{
		if ((*tkn) -> type == R_IN)
		{
			if ((*tkn) -> next)
				(*command) -> r_in = ft_strdup((*tkn) -> next -> value);
			else
				(*command) -> r_in = NULL;
			(*command) -> r_out = NULL;
			(*command) -> is_append = 0;
		}
		else if ((*tkn) -> type == R_OUT)
		{
			if ((*tkn) -> next)
				(*command) -> r_out = ft_strdup((*tkn) -> next -> value);
			else
				(*command) -> r_out = NULL;
			(*command) -> r_in = NULL;
			(*command) -> is_append = 0;
		}
		else if ((*tkn) -> type == R_APPEND)
		{
			if ((*tkn) -> next)
			{
				(*command) -> is_append = 1;
				(*command) -> r_out = ft_strdup((*tkn) -> next -> value);
			}
			else
			{
				(*command) -> is_append = 0;
				(*command) -> r_out = NULL;
			}
			(*command) -> r_in = NULL;
		}
		if ((*tkn) -> next -> next)
			(*tkn) = (*tkn) -> next -> next;
		else if ((*tkn) -> next && !((*tkn) -> next -> next))
			(*tkn) = NULL;
		}
	}
	else{
	(*command) -> r_in = NULL;
	(*command) -> r_out = NULL;
	(*command) -> is_append = 0;
	}
}

t_commands	*create_command(char *value, t_token **tkn)
{
	t_commands	*command;

	if (!value)
		return (NULL);
	command = malloc(sizeof(t_commands));
	if (!command)//allocation failed;
		return (NULL);
	create_command_helper(tkn, &command);
	command -> name = NULL;
	command -> args = NULL;
	command -> is_heredoc = 0;
	command -> next = NULL;
	command -> prev = NULL;
	if (!command)
	{
		free_commands(command);
		return (NULL);//alocation failed
	}
	command -> next = NULL;
	return (command);
}

