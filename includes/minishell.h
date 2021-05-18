/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 18:14:34 by abiari            #+#    #+#             */
/*   Updated: 2021/05/18 15:01:45 by ael-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>
# define S_QUOTE 9001
# define D_QUOTE 9002
# define IN_R 9003
# define OUT_R 9004
# define APP_R 9005



/*
LINKED LIST
*/

typedef struct	s_redirect
{
	int	type;
	char **cmd;
	char *file;
	struct s_redirect *next;
}				t_redirect;

// Separated by |
typedef struct	s_pipeline
{
	char **cmd;
	t_redirect *redirections;
	struct s_pipeline *next;
}				t_pipeline;

// Separated By ;
typedef struct	s_cmd
{
	// char	*cmd;
	t_pipeline *pipes;
	struct s_cmd *next;
}				t_cmd;

typedef struct	s_envl
{
	char	*value;
	char	*var;
	char	*key;
}				t_envl;

typedef struct	s_quotes
{
	int		type;
	int		opens;
	int		closes;
}				t_quotes;

typedef struct	s_red
{
	int		id;
	int		index;
	int		type;
}				t_red;

typedef struct	s_globals
{
	int	status;
	int	exit_code;
}				t_globals;

extern t_globals	g_vars;

char	**reddit(char *cmd);
int		red_i_init(int index, int *array, int last, char *cmd);
int		red_type_check(char *str, int i);
int		red_len_init(int index, int *array, int last, char *cmd);
char	*fill_red(char *cmd, int index, int *array);
int		red_finder(char *str, t_list **redi, t_list **tp);
int		red_type(t_list *red, int id);
void	del_node(void *content);
void	del_node_r(void *content);
int		check_cmds_helper(char **cmds, char *cmd, t_list *tmp, int *comma);
char	**pipe_it(char *cmd);
int		char_counter(char *str, t_list *tmp, char c);
void	char_array(int *array, char *str, t_list *tmp, char c);
int		*pipes(char *str, t_list **lst);
int		last_char(int *array);
int		len_init(int index, int *comma, int last, char *cmd);
int		i_init(int index, int *comma, int last, char *cmd);
int		free_the_nipples(t_list *tmp, char **cmds, int i, int indice);
char	**parse_line(char *line);
char	*find_env_key(const char *envp);
char	*find_env_value(const char *envp);
t_list	*envp_to_envl(char *envp[]);
int		msh_cd(char *path, t_list *envl);
int		msh_pwd(t_list *envl);
void	lst_append(t_list **lst, void *content);
void	mod_env_var(char *var, char *new_value, t_list *envl);
void	add_env_var(char *var, char *value, t_list *envl);
t_envl	*find_env_var(char *var, t_list *envl);
int		parse_er(char *err, int ret);
int		quote_ends(int type, int i, char *str);
int		quotes_finder(char *str, t_list **lst);
int		is_between_quotes(int i, t_list **lst);
int		*commas(char *str, t_list **lst);
int		check_last_cmd(char *cmd, int last_comma);
char	*fill_command(char *cmd, int index, int *comma);
int		check_first_cmd(char *cmd, int first_comma);
int		cmd_counter(int *comma, char *cmd, int indice);
void	ft_free(char **tab, int n);
char	**cmds_spliter(int *comma, char *cmd);
char	**split_cmds(char *cmd);
int		only_char(char c, char *str);
int		check_cmds(char **cmds, char *cmd);
int		check_pipes_helper(char **cmds, char *cmd, t_list *tmp, int *pipe);
// void	lst_append_wa(t_list **lst, t_redirect *node);
#endif
