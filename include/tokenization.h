#ifndef TOKENIZATION_H
 #define TOKENIZATION_H

typedef enum s_token_type
{
	WORD,
	PIPE,
	R_IN,
	R_OUT,
	R_APPEND,
	R_HEREDOC,
	ENV_VAR,
	TK_SPACE,
} t_token_type;

typedef enum	s_lexer_state
{
	DEFAULT,
	IN_SINGLE_QUOTES,
	IN_DOUBLE_QUOTES,
} t_lexer_state;

typedef struct s_token
{

	char			*value;
	char			*var_value;
	int			space;
	t_token_type	type;
	t_lexer_state	state;
	struct s_token	*next;
} t_token;

typedef struct s_commands
{
	char				*name;
	char				**args;
	char				*r_in;
	char				*r_out;
	char				*r_heredoc;
	char				*error;
	int 				is_append;
	int					fd_in;
	int					fd_out;
	int					stdin_original;
	int					stdout_original;
	int					heredoc_count;
	int					arg_count;
	t_lexer_state		state;
	struct s_commands	*next;
	struct s_commands	*prev;
} t_commands;


#endif
