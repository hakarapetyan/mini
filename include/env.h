#ifndef ENV_H
# define ENV_H

typedef struct s_env_list
{
	char				*key;
	char				*value;
	struct s_env_list	*next;
} env_list;

typedef struct s_shell
{
	char			*pwd;
	char			*oldpwd;
	char			*input;
	int				shlvl;
	int				token_count;
	t_token			*token;
	env_list		*env;
	env_list		*exp;
	t_commands		*command;
	struct s_shell	*next;
} t_shell;



char		*get_the_key(char *str);
char		*get_the_value(char *str);
void		get_env_list(t_shell **shell, char *str);
void		get_exp_list(t_shell **shell, char *str);
char		**ascii_sort_env(char **env);
void		get_environment(t_shell *shell, char **env);
env_list	*add_node(char *str);
int			ft_lstsize(env_list *lst);
char		**list_to_arr(env_list *env);
char		**sorting_for_export(env_list *list);
#endif
