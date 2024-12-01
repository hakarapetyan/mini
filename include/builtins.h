#ifndef BUILTINS_H
# define BUILTINS_H






int	ft_lstsize(env_list *lst);
void	ft_putendl_fd(char *s, int fd);
int is_alpha(char *arg);
int	my_strchr(const char *s, int c);
int	add_node_to_list(env_list *list, char *argv);
char *get_value(t_shell *shell, char *key);
int check_key(env_list *list, env_list *new);

//int	ham_strlen(char *str);
//int	ham_strcmp(char *s1, char *s2);


int	builtins(t_shell *shell);
void my_echo(int count, char **args);
int my_pwd(t_shell *shell);
int my_env(int argc,t_shell *shell, char **argv);
int my_export(int argc, char **arg, t_shell *shell);
int my_unset(int size, char **arg, t_shell *shell);
int	my_cd(int argc, char **argv, t_shell *shell);       
int execute_exit(t_shell *shell);

#endif