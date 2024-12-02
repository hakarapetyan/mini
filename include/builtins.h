#ifndef BUILTINS_H
# define BUILTINS_H






// int	ft_lstsize(env_list *lst);
// void	ft_putendl_fd(char *s, int fd);
// int is_alpha(char *arg);
// int	my_strchr(const char *s, int c);
// int	add_node_to_list(env_list *list, char *argv);
// char *get_value(t_shell *shell, char *key);
// int check_key(env_list *list, env_list *new);

// //int	ham_strlen(char *str);
// //int	ham_strcmp(char *s1, char *s2);


// int	builtins(t_shell *shell);
// void my_echo(int count, char **args);
// int my_pwd(t_shell *shell);
// int my_env(int argc,t_shell *shell, char **argv);
// int my_export(int argc, char **arg, t_shell *shell);
// int my_unset(int size, char **arg, t_shell *shell);
// int	my_cd(int argc, char **argv, t_shell *shell);
// int execute_exit(t_shell *shell);



//builtins
int		my_pwd(t_shell *shell);
int		execute_pwd(t_shell *shell);
void	my_echo_helper_one(int argc, char **input, int i);
void	my_echo_helper_two(int argc, char **input, int i);
void	my_echo(int argc, char **input);
void	execute_echo(t_shell *shell);
int		ham_strlen(char *str);
int		ham_strcmp(char *s1, char *s2);
int		my_cd_helper(char *argv,t_shell *shell);
int		my_cd(int argc, char **argv, t_shell *shell);
void	changes_in_list(env_list *list, char *pwd,char *oldpwd);
//void	changes_in_exp(t_shell *shell, char *pwd,char *oldpwd);
char	*get_value(t_shell *shell, char *key);
int		execute_cd(t_shell *shell);
int		is_digit_unset(char *arg);
int		my_exit(int args, char **argv, t_shell *shell);
//int		check_int(char *arg);
void	execute_exit(t_shell *shell);
void	ft_putendl_fd(char *s, int fd);
int		is_alpha(char *arg);
int		is_digit_unset(char *arg);
int		my_strchr(const char *s, int c);
int		my_unset(int size, char **arg, t_shell *shell);
int		del_from_lst(env_list *env, char *nv);
int		del_one(env_list *env);
void	write_print(char *arg, char * msg, int fd);
int		execute_unset(t_shell *shell);
int		my_env(int argc,t_shell *shell, char **arg);
int		my_env_helper(t_shell *shell, char **argv, int i);
int		execute_env(t_shell *shell);
int		add_node_to_list(env_list *env, char *argv);
int		my_export(int size, char **arg, t_shell *shell);
int		execute_export(t_shell *shell);
int		check_key(env_list *list, env_list *new);
void	print_exp_helper(char *exp);
int		my_export_helper(char **arg, env_list *env, env_list *exp);
int		builtins(t_shell *shell);

#endif
