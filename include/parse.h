#ifndef PARSE_H
# define PARSE_H


int heredoc_handle(t_shell *shell);


int		create_commands(t_shell *shell);
void	add_command(t_token **tkn, t_commands **tmp, t_shell *shell);
void	get_args(t_token **token, t_shell *shell);
t_commands	*create_command(char *value);

int	is_redirection(t_token_type type);
int	args_count(t_token **token);
//t_commands	*create_command(t_token **token, t_shell **shell);
#endif
