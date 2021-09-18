/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_norm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 17:48:17 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/09/18 17:49:09 by ael-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	lst_append_pipe(t_pipeline **list, t_pipeline *param)
{
	if ((*list))
		lst_append_pipe(&(*list)->next, param);
	else
		(*list) = param;
}

t_pipeline	*fill_pipe_lst(int v, char **pipelist, t_list **envl)
{
	t_pipeline	*pipe_list;
	char		**red;

	red = NULL;
	pipe_list = malloc(sizeof(t_pipeline));
	pipe_list->has_red = 0;
	pipe_list->redirections = NULL;
	red = reddit(pipelist[v]);
	if (red)
	{
		pipe_list->has_red = 1;
		pipe_list->redirections = red_lst(red, pipelist[v], pipe_list, envl);
		pipe_list->cmd = space_it(red[0]);
	}
	else
	{
		pipe_list->cmd = space_it(pipelist[v]);
		pipe_list->redirections = NULL;
	}
	if (red)
		free_chard(red);
	pipe_list->next = NULL;
	return (pipe_list);
}

t_pipeline	*pipe_lst(char **pipelist, t_cmd *cmd_list, t_list **envl)
{
	t_pipeline	*pipe_list;
	int			v;

	v = -1;
	cmd_list->pipes = NULL;
	while (pipelist[++v])
	{
		pipe_list = fill_pipe_lst(v, pipelist, envl);
		lst_append_pipe(&(cmd_list->pipes), pipe_list);
	}
	return (cmd_list->pipes);
}

t_cmd	*cmd_lst(char **pipelist, t_list **envl)
{
	t_cmd	*cmd_list;

	cmd_list = malloc(sizeof(t_cmd));
	cmd_list->pipes = pipe_lst(pipelist, cmd_list, envl);
	return (cmd_list);
}

int	check_reds(char **pipe)
{
	int		i;
	int		j;
	char	**red;

	i = -1;
	while (pipe[++i])
	{
		red = reddit(pipe[i]);
		j = 0;
		if (red)
		{
			while (red[++j])
			{
				if (only_char(' ', red[j]))
				{
					free_chard(red);
					ft_putstr_fd("syntax error near`>'\n", 2);
					return (0);
				}
			}
			free_chard(red);
		}
	}
	return (1);
}
