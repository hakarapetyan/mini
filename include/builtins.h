#ifndef BUILTINS_H
# define BUILTINS_H
# define INTERACTIVE	1
# define NINTERACTIVE	2
# define HEREDOC		3

# define MAX_MIN 9223372036854775808UL

char	*ft_tolower(char *str);
int		my_pwd(t_shell *shell);
void	my_echo_helper_one(int argc, char **input, int i);
void	my_echo_helper_two(int argc, char **input, int i);
void	my_echo(int argc, char **input);
int		ham_strlen(char *str);
int		ham_strcmp(char *s1, char *s2);
int		my_cd_helper(char *argv,t_shell *shell);
int		my_cd(int argc, char **argv, t_shell *shell);
int		cd_errors_checking(char *oldpwd, char *home);
void	changes_in_list(env_list *list, char *pwd,char *oldpwd);
//void	changes_in_exp(t_shell *shell, char *pwd,char *oldpwd);
char	*get_value(t_shell *shell, char *key);
int		is_digit_unset(char *arg);
int		my_exit(int args, char **argv);
int		exit_status(char *argv);
int		max_min(char *str, int sign, int *flag);
unsigned long	long_atoi(const char *str, int *flag);
//int		check_int(char *arg);
int		ft_atoi(const char *str);
void	execute_exit(t_shell *shell);
void	ft_putendl_fd(char *s, int fd);
int		is_alpha(char *arg);
int		is_digit_unset(char *arg);
int		my_strchr(char *s, int c);
int		my_unset(int size, char **arg, t_shell *shell);
int		del_from_lst(env_list *env, char *nv);
int		del_one(env_list *env);
void	write_print(char *arg, char * msg, int fd);
int		my_env(int argc,t_shell *shell, char **arg);
int		add_node_to_list(env_list *env, char *argv);
int		my_export(int size, char **arg, t_shell *shell);
int		my_isalnum(int c);
int		check_two_keies(env_list *list, env_list *new);
void	print_exp_helper(char *exp);
int		my_export_helper(char **arg, env_list *env, env_list *exp);
int		builtins(t_shell *shell);
void	signals(int num);
int		check_key(env_list *env, char *key);
char	*inc_shlvl(t_shell *shell);
void	chang_shlvl(t_shell *shell);

#endif
