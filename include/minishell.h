#ifndef MINISHELL_H
# define MINISHELL_H
# define INT_MAX_8 "9223372036854775807"
# define INT_MIN_8 "-9223372036854775808"

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <fcntl.h>
# include "tokenization.h"
# include "env.h"
# include "parse.h"
# include "errors.h"
# include "free.h"

void execute_command(t_commands *cmd);

char *extract_var(char *str, t_shell *shell);

char *extract_whitespace(char **current);

char	*var_without_quotes(t_shell *shell, char **str);


char	*generate_spaces(int count);
char	*add_space_to_env_var(char *str, char *tmp);



//builtins
int		my_pwd(t_shell *shell);
int		execute_pwd(t_shell *shell);
void	my_echo_helper_one(int argc, char **input, int i);
void	my_echo_helper_two(int argc, char **input, int i);
void	my_echo(int argc, char **input);
void	execute_echo(t_shell *shell);
int		ham_strlen(char *str);
int		ham_strcmp(char *s1, char *s2);
int		my_cd_helper(char **argv, int i, t_shell *shell);
int		my_cd(int argc, char **argv, t_shell *shell);
void	changes_in_list(env_list *list, char *pwd,char *oldpwd);
//void	changes_in_exp(t_shell *shell, char *pwd,char *oldpwd);
char	*get_value(t_shell *shell, char *key);
int		execute_cd(t_shell *shell);
int		is_digit_unset(char *arg);
int		my_exit(int args, char **argv, t_shell *shell);
int		check_int(char *arg);
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
int		add_node_to_list(env_list *env, char **argv, int i);
int		my_export(int size, char **arg, t_shell *shell);
int		execute_export(t_shell *shell);
int		check_key(env_list *list, env_list *new);
void	print_exp_helper(char *exp);
int		my_export_helper(char **arg, env_list *env, env_list *exp);

void	init_shell(t_shell *shell);

//lexical_analyzer
void	lexical_analyzer(t_shell *shell);
void	handle_special_chars(t_shell *shell, char *current);
char	*extract_env_var(char **current,t_shell *shell);
char	*extract_separator(char **current);
int		tokenization(t_shell *shell);
void	expand_var(t_shell *shell);
void	add_space(t_shell *shell, char **current, int *flag);

//create_token
t_token	*create_token(t_token_type type, t_lexer_state state, char *value);
void	add_token(t_shell *shell,t_token_type type, t_lexer_state state, char *value);
void	print_tokens(t_shell *shell);

void	print_env(t_shell *shell);
void	print_exp(t_shell *shell);


//utils_1
char	*ft_substr(char *s, unsigned int start, size_t len);
size_t	ft_strlen(char *s);
char	*ft_strdup(char *s1);
int		spec_strcmp(const char *s1, const char *s2);
int		ft_strcmp(const char *s1, const char *s2);

//utils
int		is_space(int c);
int		ft_isalnum(int c);
int		is_separator(char c);
int		is_quote(char c);
int		are_quotes_even(char *str);


///utils2
char	*is_key(env_list	*node, char *need_to_be_find);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strchr(char *str, char c);
char	*ft_strdup_interval(char **str,int *len);
int		set_state(char c, int state);

//
void	expand_var(t_shell *shell);
void	expand_heredoc(t_shell *shell);
int		is_word(char *str);



//utils3

t_token *get_last_token(t_shell *shell);
//extract_word
char	*extract_word(char **current, t_shell *shell);
char	*extract_quoted_str(char **current, t_shell *shell);
char	*extract_var_from_quoted_str(char *str, t_shell *shell);
char	*var_in_quotes(t_shell *shell, char **str);

int	ft_search(char	*str, t_shell *shell);

#endif
