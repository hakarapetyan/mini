#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include "get_next_line.h"
# include "tokenization.h"
# include "env.h"
# include "parse.h"
# include "errors.h"
# include "free.h"

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


//extract_word
char	*extract_word(char **current, t_shell *shell);
char	*extract_quoted_str(char **current, t_shell *shell);
char	*extract_var_from_quoted_str(char *str, t_shell *shell);
char	*var_in_quotes(t_shell *shell, char **str);

int	ft_search(char	*str, t_shell *shell);

#endif
