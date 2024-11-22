#include "./include/minishell.h"


int	g_exit_status;


void set_status(int status)
{
	g_exit_status = status;
}
