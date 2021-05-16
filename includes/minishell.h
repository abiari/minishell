/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 18:14:34 by abiari            #+#    #+#             */
/*   Updated: 2021/05/15 08:26:22 by abiari           ###   ########.fr       */
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
# include <sys/wait.h>
# define S_QUOTE 9001
# define D_QUOTE 9002
# define IN_R 9003
# define OUT_R 9004
# define APP_R 9005

typedef struct	s_redirect
{
	int	type;
	char **cmd;
	char *fd;
	struct s_redirect *next;
}				t_redirect;

typedef struct	s_pipeline
{
	char *line;
	t_redirect *redirections;
	struct s_pipeline *next;
}				t_pipeline;

typedef struct	s_cmd
{
	char *line;
	t_pipeline *pipes;
	struct s_cmd *next;
}				t_cmd;

typedef struct	s_envl
{
	char	*key;
	char	*value;
	char	*var;
	int		env_printable;
}				t_envl;

typedef struct	s_globals
{
	int	status;
	int	exit_code;
}				t_globals;

extern t_globals	g_vars;

char	*find_env_key(const char *envp);
char	*find_env_value(const char *envp);
t_list	*envp_to_envl(char *envp[]);
int		msh_cd(char *path, t_list *envl);
int		msh_pwd(t_list *envl);
int		msh_unset(char *args[], t_list *envl);
int		msh_env(t_list **envl);
int		msh_export(char **args, t_list **envl);
void	lst_append(t_list **lst, void *content);
void	mod_env_var(char *var, char *new_value, t_list **envl);
void	add_env_var(char *var, char *value, t_list **envl);
void	envl_clear(void *content);
int		delete_env_var(char *var, t_list **envl);
t_envl	*find_env_var(char *var, t_list **envl);
char	*bin_path(char *cmd, t_list *envl);
void	free_double(char **arr);
#endif
