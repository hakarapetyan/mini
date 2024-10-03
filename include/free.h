#ifndef FREE_H
# define FREE_H

void	free_env(env_list *env);
void	free_tokens(t_token *token);
void	free_commands(t_commands *command);
void	free_shell(t_shell *shell);
void	free_str(char	*str);
void	free_arr(char **arr);
void	free_args(char **args);
#endif
