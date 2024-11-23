#include "./include/minishell.h"

// static int heredoc_arguments(t_commands *command)
// {
// 	while
// }
int heredoc_handle(t_shell *shell)
{
	t_commands *cmd = shell -> command;
	char	*delimiter;
	char	**files;
	int fd = 0;


	delimiter = NULL;
	if (cmd -> r_heredoc)
	{
		fd = open("tmp_file", O_WRONLY | O_CREAT | O_TRUNC, 0600);
		while (1)
		{
			delimiter = readline("< ");
			if (ft_strcmp(delimiter, cmd -> r_heredoc) == 0)
				break;
			write(fd, delimiter, ft_strlen(delimiter));
			write(fd, "\n", 1);
		}
		fd = open("tmp_file", O_RDONLY);
		if (fd < 0)
		{
			perror("");
		}
		cmd -> fd_in = fd;
		//heredoc_arguments(cmd);
	}

}
