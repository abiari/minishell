/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 18:14:34 by abiari            #+#    #+#             */
/*   Updated: 2021/04/19 14:26:08 by ael-bagh         ###   ########.fr       */
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



/*
LINKED LIST
*/

// Separated By ;
typedef struct	s_cmd
{
	char *line;
	t_pipeline *pipes;
	struct s_cmd *next;
}				t_cmd;

// Separated by |
typedef struct	s_pipeline
{
	char *line;
	t_redirect *redirections;
	struct s_pipeline *next;
}				t_pipeline;


typedef struct	s_redirect
{
	char *line;
	char **args;
	char **redirect;
	struct s_redirect *next;
}				t_redirect;

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

int		g_status;

void	del_node(void *content);
int		last_comma(int *commas);
int		len_init(int index, int *comma, int last, char *cmd);
int		i_init(int index, int *comma, int last, char *cmd);
int		free_the_nipples(t_list *tmp, char **cmds, int i);
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
int		cmd_counter(int *comma, char *cmd);
void	ft_free(char **tab, int n);
char	**cmds_spliter(int *comma, char *cmd);
char	**split_cmds(char *cmd);
int		only_char(char c, char *str);
int		check_cmds(char **cmds, char *cmd);
#endif
