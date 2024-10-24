NAME = minishell

RM = rm -f

CFLAGS = -Wall  -Wextra -fsanitize=address -g3

INCLUDE = ./include/minishell.h\
			./include/env.h\
			./include/tokenization.h\

SRCS =  main.c\
		get_environment.c\
		init_shell.c\
		lexical_analyzer.c\
		create_token.c\
		expand_var.c\
		extract_word.c\
		create_commands.c\
		builtins.c\
		error.c\
		free.c\
		utils.c\
		utils_1.c\
		utils_2.c\
		utils_3.c\
		another_builtins.c\



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
