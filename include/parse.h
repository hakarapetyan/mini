#ifndef PARSE_H
# define PARSE_H

void		create_commands(t_shell *shell);
void	add_command(t_token **tkn, t_commands **tmp, t_shell *shell);
void	get_args(t_token **token, t_shell *shell);
t_commands	*create_command(char *value, t_token **tkn);
void	add_args(t_token **token, t_commands **tmp, t_shell *shell);

int	is_redirection(t_token_type type);
int	args_count(t_token **token);
//t_commands	*create_command(t_token **token, t_shell **shell);
#endif
