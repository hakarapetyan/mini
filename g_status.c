#include "./include/minishell.h"


int	g_exit_status;


void set_status(int status)
{
	g_exit_status = status;
	printf("%d\n",g_exit_status);
}
int get_status(void)
{
	return (g_exit_status);
}
