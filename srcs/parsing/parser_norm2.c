/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_norm2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 17:49:31 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/09/18 17:49:53 by ael-bagh         ###   ########.fr       */
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

int	check_pipes(char **pipe, char *cmd)
{
	int		*pipe_arr;
	t_list	*tmp;

	if (pipe == NULL)
		return (1);
	tmp = NULL;
	quotes_finder(cmd, &tmp);
	pipe_arr = pipes(cmd, &tmp);
	if (pipe_arr != NULL)
		return (check_pipes_helper(pipe, cmd, tmp, pipe_arr));
	ft_lstclear(&tmp, del_node);
	return (0);
}

void	lst_append_red(t_redirect **list, t_redirect *param)
{
	if ((*list))
		lst_append_red(&(*list)->next, param);
	else
		(*list) = param;
}

t_redirect	*fill_red_lst(t_list *reds, int v, char **red)
{
	t_redirect	*red_list;

	red_list = malloc(sizeof(t_redirect));
	red_list->file = ft_strdup(red[v]);
	red_list->type = red_type(&reds, v);
	red_list->next = NULL;
	return (red_list);
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
	red_list = fill_red_lst(reds, v, red);
	lst_append_red(&(pipe_lst->redirections), red_list);
	head = red_list;
	while (red[++v])
	{
		red_list = fill_red_lst(reds, v, red);
		lst_append_red(&(pipe_lst->redirections), red_list);
	}
	ft_lstclear(&reds, del_node_r);
	return (head);
}
