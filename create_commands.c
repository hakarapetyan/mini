#include "./include/minishell.h"

void	create_commands(t_shell *shell)
{
	t_token		*tkn;
	t_commands	*tmp;

	if (!shell -> token)
		error(ALLOCATION_ERR, shell);
	tmp = shell -> command;
	tkn = shell -> token;
	if (tkn)
	{
		while (tkn)
		{
			if (!(tmp))
			{
				tmp = create_command(shell -> token -> value, shell -> token -> var_value);
				shell -> command = tmp;
				if (!(shell -> command))
					error(ALLOCATION_ERR, shell);
			}
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
	*type = ft_strdup((*token) -> next -> value);
	if (!(*type))
		error(ALLOCATION_ERR, shell);
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
	(*token) = (*token) -> next -> next;
}


void	add_args(t_token **token,t_commands **tmp,  t_shell *shell)
{
	int	i;

	i = 0;

	while ((*token) && (*token) -> type != PIPE)
	{
		if (is_redirection((*token) -> type))
		{
			get_redir(token, tmp, shell);
		}
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

void	parse_redir(t_token **tkn, t_commands **tmp, t_shell *shell)
{
	while ((*tmp) -> next)
		(*tmp) = (*tmp) -> next;
	(*tmp) -> r_in = ft_strdup((*tkn) -> next -> value);
	if (!((*tmp)))
		free_shell(shell);
	(*tmp)  -> prev = *tmp;
	(*tkn) = (*tkn) -> next;
	(*tmp) = (*tmp) -> next;
}
void	add_command(t_token **tkn, t_commands **tmp, t_shell *shell)
{

	if (!ft_strcmp((*tkn) -> value, "|"))
	{
		while ((*tmp) -> next)
			(*tmp) = (*tmp) -> next;
		(*tmp) -> next = create_command((*tkn) -> next -> value, (*tkn) -> next -> var_value);
		if (!((*tmp) -> next))
			free_shell(shell);
		(*tmp) -> next -> prev = *tmp;
		(*tkn) = (*tkn) -> next;
		(*tmp) = (*tmp) -> next;
	}
}

t_commands	*create_command(char *value, char *var_value)
{
	t_commands	*command;

	if (!value)
		return (NULL);
	(void)var_value;
	command = malloc(sizeof(t_commands));
	if (!command)//allocation failed;
		return (NULL);
		// printf("varval%s\n",var_value);
		// printf("val%s\n",value);
	// if (*var_value)
	// {
	// 	command -> name = ft_strdup(var_value);
	// }
	// else
		command -> name = ft_strdup(value);
	command -> args = NULL;
	command -> r_in = NULL;
	command -> r_out = NULL;
	command -> is_append = 0;
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
