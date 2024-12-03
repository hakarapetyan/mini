#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
#include <dirent.h>
# include "tokenization.h"
# include "env.h"
# include "builtins.h"
# include "parse.h"
# include "errors.h"
# include "free.h"

# define SUCCESS 0
# define FAILURE 1
# define BUILTIN_ERROR 2
# define CMD_NOT_EXEC 126
# define CMD_NOT_FOUND 127
# define EXIT_OUT_OF_RANGE 255
# define SYNTAX_ERROR 258



int prepare_redirections(t_shell *shell);

void	get_redir(t_token **token,t_commands **tmp,  t_shell *shell);

char	*ft_itoa(int n);
void	print_commands(t_shell *shell);
//void execute_execve(t_shell *shell);
//find_path
char	*find_path(t_shell *shell, char	*command_name);

//execute
void	execute_command(t_shell *shell);
int		is_builtin(char *name);

//ft_split
char	**ft_split(char const *s, char c);

//void execute_command(t_commands *cmd);

//char *extract_var(char *str, t_shell *shell);

char	*extract_whitespace(char **current);

//char	*var_without_quotes(t_shell *shell, char **str);


char	*generate_spaces(int count);


void	token_count(t_shell *shell);
//builtins
//void	my_pwd(void);
void	my_echo_helper_one(int argc, char **input, int i);
void	my_echo_helper_two(int argc, char **input, int i);
void	my_echo(int argc, char **input);
// void	execute_echo(t_shell *shell);
// int		ham_strlen(char *str);
// int		ham_strcmp(char *s1, char *s2);

void	init_shell(t_shell *shell);

//lexical_analyzer
void	lexical_analyzer(t_shell *shell);
void	handle_special_chars(t_shell *shell, char *current);
char	*extract_separator(char **current);
int		tokenization(t_shell *shell);
void	expand_var(t_shell *shell);
//void	add_space(t_shell *shell, char **current, int *flag);

//create_token
//t_token	*create_token(t_shell *shell, t_token_type type, t_lexer_state state, char *value);
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
int		is_sep(char c);


///utils2
char	*is_key(env_list	*node, char *need_to_be_find);
char	*ft_strjoin(char *s1, char *s2);
char	*another_strjoin(char *s1, char *s2);
int		ft_strchr(char *str, char c);
char	*ft_strdup_interval(char **str,int *len);
int		set_state(char c, int state);

//
void	expand_var(t_shell *shell);




//utils3

t_token *get_last_token(t_shell *shell);
t_commands *get_last_command(t_shell *shell);
t_token *get_the_token_i_want(t_shell *shell);
//int	redir_check(t_token_type type,t_shell *shell);


//extract_word
char	*extract_word(char **current, t_shell *shell);
char	*extract_var_from_quoted_str(char *str, t_shell *shell);
//char	*var_in_quotes(t_shell *shell, char **str);

int		var_search(char	*str, t_shell *shell);

#endif
