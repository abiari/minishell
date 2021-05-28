/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 13:37:19 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/05/28 17:40:58 by ael-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	int		ret;

	tmp = NULL;
	ret = quotes_finder(cmd, &tmp);
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

t_redirect	*red_lst(char **red, char *cmd, t_pipeline *pipe_lst)
{
	t_redirect	*red_list;
	t_list	*quotes;
	t_list	*reds;
	int		v;

	reds = NULL;
	quotes = NULL;
	pipe_lst->redirections = NULL;
	v = quotes_finder(cmd, &quotes);
	v = red_finder(cmd, &reds, &quotes);
	v = 0;
	red_list = NULL;
	while (red[++v])
	{
		//printf("redirection :%s\n", red[v]);
		red_list = malloc(sizeof(t_redirect));
		red_list->file = red[v];
		red_list->type = red_type(&reds, v);
		red_list->next = NULL;
		lst_append_red(&(pipe_lst->redirections), red_list);
	}
	return (red_list);
}

void lst_append_pipe(t_pipeline **list, t_pipeline *param) {
	if ((*list))
		lst_append_pipe(&(*list)->next, param);
	else
		(*list) = param;
}

t_pipeline	*pipe_lst(char **pipelist, char **red, char *cmd, t_cmd *cmd_list)
{
	t_pipeline	*pipe_list;
	int			v;

	v = -1;
	cmd_list->pipes = NULL;
	while (pipelist[++v])
	{
		pipe_list = malloc(sizeof(t_pipeline));
		pipe_list->has_red = 0;
		pipe_list->redirections = NULL;
		if (red)
		{
			pipe_list->has_red = 1;
			pipe_list->redirections = red_lst(red, cmd, pipe_list);
			pipe_list->cmd	= ft_split(red[0], ' ');
		}
		else
		{
			pipe_list->cmd	= ft_split(pipelist[v], ' ');
			pipe_list->redirections = NULL;
		}
		pipe_list->next = NULL;
		lst_append_pipe(&(cmd_list->pipes), pipe_list);
	}
	return (pipe_list);
}

t_cmd	*cmd_lst(char **pipelist, char **red, char *cmd)
{
	t_cmd *cmd_list;

	cmd_list = malloc(sizeof(t_cmd));
	cmd_list->pipes = pipe_lst(pipelist, red, cmd, cmd_list);
	cmd_list->next = NULL;
	return(cmd_list);
}

t_list		*main_lst(void)
{
	int		i;
	int		j;
	int		x;
	char	**tab;
	char	**pipe;
	char	*cmd;
	char	**red;
	t_cmd	*cmd_list;
	t_list	*main_list;


	i = 0;
	x = 0;
	main_list = NULL;
	tab = NULL;
	cmd = ft_strdup("echo hello > file world > file2 ! | command > file80 concat1 > file21 concat2;");
	tab = split_cmds(cmd);
	if (tab)
		if (check_cmds(tab, cmd) == 1)
			return (NULL);
	while (tab[i])
	{
		pipe = pipe_it(tab[i]);
		if (check_pipes(pipe, tab[i]) == 1)
			return (NULL);
		j = -1;
		while (pipe[++j])
		{
			red = reddit(pipe[j]);
			cmd_list = cmd_lst(pipe, red, pipe[j]);
			lst_append(&main_list, cmd_list);
		}
		i++;
	}
	free(cmd);
	return (main_list);
}

int	main(void)
{
	t_list	*cmd;
	int		i;

	i = -1;
	cmd = main_lst();
	if (cmd == NULL)
		return (1);
	while (cmd)
	{
		while (((t_cmd *)cmd->content)->pipes)
		{
			i = -1;
			printf("command:\n");
			while (((t_cmd *)cmd->content)->pipes->cmd[++i])
				printf("|%s|", ((t_cmd *)cmd->content)->pipes->cmd[i]);
			printf("\n");
			if (((t_cmd *)cmd->content)->pipes->has_red)
			{
				while (((t_cmd *)cmd->content)->pipes->redirections)
				{
					i = 0;
					printf("redirections:\n");
					printf("file[%d]:|%s|\n",i , ((t_cmd *)cmd->content)->pipes->redirections->file);
					((t_cmd *)cmd->content)->pipes->redirections = ((t_cmd *)cmd->content)->pipes->redirections->next;
					i++;
				}
			}
			((t_cmd *)cmd->content)->pipes = ((t_cmd *)cmd->content)->pipes->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
