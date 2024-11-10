#include "./include/minishell.h"

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
			if (!(tmp))
			{
				tmp = create_command(shell -> token -> value, shell -> token -> var_value);
				shell -> command = tmp;
				if (!(shell -> command))
					error(ALLOCATION_ERR, shell);
				shell -> command_count++;
			}
			else
				add_command(&tkn, &tmp, shell);
			get_args(&tkn, shell);
		}
	}
}

// void	open_the_file(t_shell *shell, char *file)
// {
// //	t_commands	*cmnd;
// 	int	fd;

// 	fd = -1;
// 	(void)shell;
// 	//cmnd = shell -> command;
// 	if (file)
// 	{
// 		fd = open(file, O_RDONLY);
// 		if (fd < 0)
// 		{
// 			perror("Error opening file\n");
// 			//error("Error opening file", shell);
// 		}
// 	}
// 	if (fd >= 0)
// 		close(fd);
// }

// void execute_command(t_commands *cmd)
// {
//    // pid_t pid = fork();

// 	if (cmd->name == NULL || cmd->args == NULL) {
//     fprintf(stderr, "Command name or arguments are not set.\n");
//     exit(EXIT_FAILURE);
// 	}

//     //if (pid == 0) {
//         // if (cmd->r_in) {
//         //     int fd_in = open(cmd->r_in, O_RDONLY);
//         //     if (fd_in < 0) {
//         //         perror(cmd->r_in);
//         //         exit(EXIT_FAILURE);
//         //     }
//         //     if (dup2(fd_in, STDIN_FILENO) < 0) {
//         //         perror("dup2");
//         //         close(fd_in);
//         //         exit(EXIT_FAILURE);
//         //     }
//         //     close(fd_in);
//         // }

//         // if (cmd->r_out) {
//         //     int fd_out = open(cmd->r_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
//         //     if (fd_out < 0) {
//         //         perror(cmd -> r_out);
//         //         exit(EXIT_FAILURE);
//         //     }
//         //     if (dup2(fd_out, STDOUT_FILENO) < 0) {
//         //         perror("dup2");
//         //         close(fd_out);
//         //         exit(EXIT_FAILURE);
//         //     }
//         //     close(fd_out);
//         // }


        // if (cmd->is_append) {
        //     int fd_append = open(cmd->is_append, O_WRONLY | O_CREAT | O_APPEND, 0644);
        //     if (fd_append < 0) {
        //         perror("open");
        //         exit(EXIT_FAILURE);
        //     }
        //     if (dup2(fd_append, STDOUT_FILENO) < 0) {
        //         perror("dup2");
        //         close(fd_append);
        //         exit(EXIT_FAILURE);
        //     }
        //     close(fd_append);
        // }

//         if (execvp(cmd->name, cmd->args) == -1) {
//             perror("execvp");
//             exit(EXIT_FAILURE);
// 		   }
//     // } else if (pid < 0) {
//     //     perror("fork");
//     // } else {
//     //     wait(NULL);
//     // }
// }


static void	get_redir_helper(t_token **token,  t_shell *shell, char **type)
{
	if (*type)
		free(*type);
	if (*token && (*token) -> next)
		*type = ft_strdup((*token) -> next -> value);
		printf("type = %s\n",*type);
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
		shell -> command_count++;
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
