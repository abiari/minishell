/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 18:14:34 by abiari            #+#    #+#             */
/*   Updated: 2021/09/19 08:46:50 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <string.h>
# include <errno.h>
# include <dirent.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# define S_QUOTE 9001
# define D_QUOTE 9002
# define OUT_R 9003
# define IN_R 9004
# define APP_R 9005
# define DOC_R 9008
# define FALSE 9006
# define TRUE 9007

typedef struct s_redirect
{
	int					type;
	char				*file;
	struct s_redirect	*next;
}				t_redirect;

// Separated by |
typedef struct s_pipeline
{
	char				**cmd;
	int					has_red;
	t_redirect			*redirections;
	struct s_pipeline	*next;
}				t_pipeline;

// Separated By ;
typedef struct s_cmd
{
	t_pipeline		*pipes;
}				t_cmd;

typedef struct s_quotes
{
	int		type;
	int		opens;
	int		closes;
}				t_quotes;

typedef struct s_red
{
	int		id;
	int		index;
	int		type;
}				t_red;

typedef struct s_envl
{
	char	*key;
	char	*value;
	char	*var;
	int		env_printable;
}				t_envl;

typedef struct s_globals
{
	int		status;
	pid_t	pid;
	int		exit_code;
}				t_globals;

t_globals	g_vars;

void		free_chard(char **str);
char		*find_env_key(const char *envp);
char		*find_env_value(const char *envp);
t_list		*envp_to_envl(char *envp[]);
char		**envl_to_envp(t_list **envl);
int			msh_cd(char **args, t_list **envl);
int			msh_pwd(char **args, t_list **envl);
int			msh_unset(char **args, t_list **envl);
int			msh_env(char **args, t_list **envl);
int			msh_export(char **args, t_list **envl);
int			msh_exit(char **args, t_list **envl);
int			msh_echo(char **args, t_list **envl);
void		lst_append(t_list **lst, void *content);
void		mod_env_var(char *var, char *new_value, t_list **envl);
void		add_env_var(char *var, char *value, t_list **envl);
void		envl_clear(void *content);
int			delete_env_var(char *var, t_list **envl);
t_envl		*find_env_var(char *var, t_list **envl);
char		*bin_path(char *cmd, t_list *envl);
void		free_double(char **arr, int i);
void		fork_pipes(t_pipeline *cmd, t_list **envl);
void		redirect(t_pipeline *cmd);
void		sig_handler(int sign_num);
void		exec(t_pipeline *cmd, t_list **envl);
void		process(int sign_num);
void		sig_handler(int sign_num);
void		create_file(t_pipeline *cmd);
int			is_builtin(char *cmd);
int			exec_builtin(char **cmd, t_list **envl);
char		*rand_str(void);
char		*ft_ll_itoa(long long n);
void		heredoc_spawn(t_pipeline *cmd);
void		heredoc(char *stop_value, int fd);
char		*heredoc_helper(char *stop_value);
int			is_dir(char *exec);
char		*check_exec(char *cmd, t_list *envl);
int			is_builtin(char *cmd);
int			check_if_builtin(t_pipeline *cmd, t_list **envl);
void		export_err(char *str);
void		print_env(t_list **envl);
void		is_printable(int *prnt, char *haystack);
int			heredoc_count(t_redirect *reds);
int			check_key(char *arg);
void		msh_prompt(void);
char		*magic_touch(char *str);
char		*expand(char *tab, t_list **envl);
char		*ft_strndup(const char *src, int n);
int			is_valid_quote(int	i, t_list **lst);
char		**spank_it(char **tab, t_list **envl);
int			space_counter(int *comma);
int			two_d_counter(char **two_d);
char		**space_spliter(int *space, char *cmd);
int			*spaces(char *str, t_list **lst);
char		**space_it(char *red);
char		*split_ws(char *red);
char		*get_cmd(char **red, char **pipelist);
char		**reddit(char *cmd);
int			red_i_init(int index, int *array, int last, char *cmd);
int			red_type_check(char *str, int i);
int			red_len_init(int index, int *array, int last, char *cmd);
char		*fill_red(char *cmd, int index, int *array);
int			red_finder(char *str, t_list **redi, t_list **tp);
int			red_type(t_list **red, int id);
void		del_node(void *content);
void		del_node_r(void *content);
void		delist(void *content);
char		**pipe_it(char *cmd);
int			char_counter(char *str, t_list *tmp, char c);
void		char_array(int *array, char *str, t_list *tmp, char c);
int			*pipes(char *str, t_list **lst);
int			last_char(int *array);
int			len_init(int index, int *comma, int last, char *cmd);
int			i_init(int index, int *comma, int last, char *cmd);
int			free_them(t_list *tmp, char **cmds, int i, int indice);
int			quote_ends(int type, int i, char *str);
int			quotes_finder(char *str, t_list **lst);
int			bq(int i, t_list **lst);
int			*commas(char *str, t_list **lst);
int			check_last_cmd(char *cmd, int last_comma);
char		*fill_command(char *cmd, int index, int *comma);
int			check_first_cmd(char *cmd, int first_comma);
int			cmd_counter(int *comma, char *cmd, int indice);
void		ft_free(char **tab, int n);
int			only_char(char c, char *str);
int			check_pipes_helper(char **cmds, char *cmd, t_list *tmp, int *pipe);
char		**parse_line(char *line);
int			parse_er(char *err, int ret);
char		*quote_error(void);
t_list		*main_lst(char *cmd, t_list **envl);
char		**pipe_spliter(int *pipe, char *cmd);
int			free_pipes(int *p, t_list *t, char **c, int tmp);
int			only_char(char c, char *str);
int			free_them(t_list *tmp, char **cmds, int i, int indice);
int			is_gucci(char c, int i);
int			dollar_finder(char *str, t_list **quotes);
int			red_counter(char *str, t_list *tmp);
void		red_array(int *array, char *str, t_list *tmp);
int			validate_red(char *str, int i, t_list *tmp);
int			red_type_check(char *str, int i);
int			ret_count(int count, int i);
char		*my_strjoin(char *s1, char const *s2);
char		*to_join(char **spaces);
int			*reds(char *str, t_list **lst);
void		spaces_array(int *spaces, char *str, t_list *tmp, char c);
int			spaces_count(char *str, t_list *tmp, char c);
char		*between_valid_spaces(char *cmd, int index, int	*space);
int			check_reds(char **pipe);
t_cmd		*cmd_lst(char **pipelist, t_list **envl);
t_redirect	*red_lst(char **red, char *cmd,
				t_pipeline *pipe_lst, t_list **envl);
int			check_pipes(char **pipe, char *cmd);
int			cd_err(char *path, char **old_path, t_list ***envl);
void		exit_if_dir(t_pipeline *cmd);
void		wait_exec(void);
int			files_in_pipe(t_pipeline **cmd, int *in, int *fd);
void		print_error(char *file);

#endif
