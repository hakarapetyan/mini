NAME = minishell

RM = rm -f

CFLAGS = -Wall  -Wextra  -fsanitize=address  -g3

INCLUDE = ./include/minishell.h\
			./include/env.h\
			./include/tokenization.h\

SRCS =  main.c\
		get_environment.c\
		get_env_helper.c\
		init_shell.c\
		lexical_analyzer.c\
		create_token.c\
		expand_var.c\
		extract_word.c\
		extract_var.c\
		var_search.c\
		create_commands.c\
		find_path.c\
		execute.c\
		ft_split.c\
		ft_itoa.c\
		g_status.c\
		heredoc.c\
		prepare_redirections.c\
		get_redir.c\
		get_args.c\
		error.c\
		free.c\
		print.c\
		utils.c\
		utils_1.c\
		utils_2.c\
		utils_3.c\
		./builtins/builtins.c\
		./builtins/utils_builtins.c\
		./builtins/cd.c\
		./builtins/cd_helper.c\
		./builtins/cd_norm.c\
		./builtins/echo.c\
		./builtins/env.c\
		./builtins/exit.c\
		./builtins/export_helper.c\
		./builtins/export.c\
		./builtins/pwd.c\
		./builtins/unset_helper.c\
		./builtins/unset.c\



OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(INCLUDE) Makefile
	cc $(CFLAGS) $(OBJS) -lreadline -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
