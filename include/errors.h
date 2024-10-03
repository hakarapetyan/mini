#ifndef ERRORS_H
# define ERRORS_H

# define SYNTAX_ERR "Syntax error!"
# define ALLOCATION_ERR "Allocation failed!"
# define QUOTE_ERR "syntax error near unexpected token `newline'"
# define READLINE_ERR "Readline failed!"

void	error(char	*err, t_shell *shell);
#endif
