/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 13:37:19 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/06/25 11:34:04 by ael-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_freex(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
	tab = NULL;
}

char	**parse_line(char *line)
{
	char	**tab;

	tab = split_cmds(line);
	if (tab)
		if (check_cmds(tab, line) == 1)
			return (NULL);
	return (tab);
}

int	check_pipes(char **pipe, char *cmd)
{
	int		*pipe_arr;
	t_list	*tmp;

	if (pipe == NULL)
		return(1);
	tmp = NULL;
	quotes_finder(cmd, &tmp);
	pipe_arr = pipes(cmd, &tmp);
	if (pipe_arr != NULL)
		return (check_pipes_helper(pipe, cmd, tmp, pipe_arr));
	return (0);
}

void lst_append_red(t_redirect **list, t_redirect *param) {
	if ((*list))
		lst_append_red(&(*list)->next, param);
	else
		(*list) = param;
}

t_redirect	*red_lst(char **red, char *cmd, t_pipeline *pipe_lst, t_list **envl)
{
	t_redirect	*red_list;
	t_redirect	*head;
	t_list		*quotes;
	t_list		*reds;
	int			v;
	(void)envl;
	reds = NULL;
	quotes = NULL;
	pipe_lst->redirections = NULL;
	v = quotes_finder(cmd, &quotes);
	v = red_finder(cmd, &reds, &quotes);
	v = 1;
	red_list = malloc(sizeof(t_redirect));
	red_list->file = ft_strdup(red[v]);
	red_list->type = red_type(&reds, v);
	red_list->next = NULL;
	lst_append_red(&(pipe_lst->redirections), red_list);
	head = red_list;
	while (red[++v])
	{
		red_list = malloc(sizeof(t_redirect));
		red_list->file = ft_strdup(red[v]);
		red_list->type = red_type(&reds, v);
		red_list->next = NULL;
		lst_append_red(&(pipe_lst->redirections), red_list);
	}
	return (head);
}

void lst_append_pipe(t_pipeline **list, t_pipeline *param) {
	if ((*list))
		lst_append_pipe(&(*list)->next, param);
	else
		(*list) = param;
}

t_pipeline	*pipe_lst(char **pipelist, t_cmd *cmd_list, t_list **envl)
{
	t_pipeline	*pipe_list;
	int			v;
	char **red;

	v = -1;
	cmd_list->pipes = NULL;
	while (pipelist[++v])
	{
		pipe_list = malloc(sizeof(t_pipeline));
		pipe_list->has_red = 0;
		pipe_list->redirections = NULL;
		red = reddit(pipelist[v]);
		if (red)
		{
			pipe_list->has_red = 1;
			pipe_list->redirections = red_lst(red, pipelist[v], pipe_list, envl);
			pipe_list->cmd	= space_it(red[0]);
		}
		else
		{
			pipe_list->cmd	= space_it(pipelist[v]);
			pipe_list->redirections = NULL;
		}
		pipe_list->next = NULL;
		lst_append_pipe(&(cmd_list->pipes), pipe_list);
	}
	return (cmd_list->pipes);
}

t_cmd	*cmd_lst(char **pipelist, t_list **envl)
{
	t_cmd *cmd_list;
	cmd_list = malloc(sizeof(t_cmd));
	cmd_list->pipes = pipe_lst(pipelist, cmd_list, envl);
	return(cmd_list);
}

t_list		*main_lst(char *cmd, t_list **envl)
{
	char	**pipe;
	char	*exp;
	t_cmd	*cmd_list;
	t_list	*main_list;

	exp = NULL;
	main_list = NULL;
	exp = expand(cmd, envl);
	pipe = pipe_it(exp);
	if (check_pipes(pipe, exp) == 1)
		return (NULL);
	cmd_list = cmd_lst(pipe, envl);
	lst_append(&main_list, cmd_list);
	free(exp);
	return (main_list);
}
