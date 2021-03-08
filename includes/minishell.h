/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 18:14:34 by abiari            #+#    #+#             */
/*   Updated: 2021/03/08 14:59:14 by abiari           ###   ########.fr       */
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

typedef struct	s_cmds
{
	char			*cmd;
	int				type;
	struct	s_cmds	*prev;
	struct	s_cmds	*next;
}				t_cmds;

typedef struct	s_envl
{
	char	*key;
	char	*value;
	char	*var;
}				t_envl;

int		g_status;

char	*find_env_key(const char *envp);
char	*find_env_value(const char *envp);
t_list	*envp_to_envl(char *envp[]);
int		msh_cd(char *path, t_list *envl);
int		msh_pwd(t_list *envl);
void	lst_append(t_list **lst, void *content);
void	mod_env_var(char *var, char *new_value, t_list *envl);
void	add_env_var(char *var, char *value, t_list *envl);
t_envl	*find_env_var(char *var, t_list *envl);
#endif
