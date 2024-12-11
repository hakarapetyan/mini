#ifndef ERRORS_H
# define ERRORS_H

# define ALLOCATION_ERR "Allocation failed"
# define READLINE_ERR "Readline failed"
# define SYNTAX_ERR_MSG "syntax error near unexpected token `"
# define GETCWDERROR "cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory"
# define CMD_NOT_FND_MSG "command not found"
# define NO_SUCH_FILE_MSG "No such file or directory"
# define PERMISSION_DENIED_MSG "Permission denied"
# define IS_DIRECTORY_MSG "Is a directory"
# define NOT_DIRECTORY_MSG "Not a directory"

# define SYNTAX_ERR 3
# define CMD_NOT_FND 4
# define NO_SUCH_FILE 5
# define PERMISSION_DENIED 6



void	error(char	*err, t_shell *shell);
void	syntax_error(char *message);

void	error_message(int status, char *command_name);
void	simple_error(int status, char *command_name, char *message);
void	another_simple_error(int status, char *command_name, char *argv, char *message);

void set_status(int status);
int get_status(void);
#endif
