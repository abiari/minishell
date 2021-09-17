/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 12:18:09 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/09/17 10:55:41 by ael-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	len_init(int index, int *array, int last, char *cmd)
{
	if (index == 0)
		return (array[index]);
	else if (index == last && check_last_cmd(cmd, array[last - 1]))
		return (ft_strlen(cmd) - array[index - 1] - 1);
	else
		return (array[index] - array[index - 1] - 1);
}

int	i_init(int index, int *array, int last, char *cmd)
{
	if (index == 0)
		return (0);
	else if (index == last && check_last_cmd(cmd, array[last - 1]))
		return (array[index - 1] + 1);
	else
		return (array[index - 1] + 1);
}

int	check_cmds_helper(char **cmds, char *cmd, t_list *tmp, int *comma)
{
	int	last;
	int	i;

	i = -1;
	last = last_char(comma);
	while (cmds[++i])
	{
		if (i == cmd_counter(comma, cmd, 0) - 1)
			if (only_char(' ', cmds[i])
				&& (comma[last - 1] == (int)ft_strlen(cmd) - 1))
				return (free_them(tmp, cmds, cmd_counter(comma, cmd, 0), 0));
		if (i != cmd_counter(comma, cmd, 0) - 1 && only_char(' ', cmds[i]))
			return (free_them(tmp, cmds, cmd_counter(comma, cmd, 0), 0));
	}
	if (comma)
		free(comma);
	ft_lstclear(&tmp, del_node);
	return (0);
}

int	check_pipes_helper(char **c, char *cmd, t_list *t, int *p)
{
	int	last;
	int	i;
	int cmd_count;

	last = last_char(p);
	i = -1;
	cmd_count = cmd_counter(p, cmd, 1);
	while (c[++i])
	{
		if (i == cmd_count - 1)
			if (only_char(' ', c[i])
				|| (p[last - 1] == (int)ft_strlen(cmd) - 1))
				{
					free(p);
					return (free_them(t, c, cmd_count, 1));
				}
		if (i != cmd_count - 1 && only_char(' ', c[i]))
		{
			free(p);
			return (free_them(t, c, cmd_count, 1));
		}
	}
	if (p)
		free(p);
	ft_lstclear(&t, del_node);
	return (0);
}

int	check_cmds(char **cmds, char *cmd)
{
	int		*comma;
	t_list	*tmp;

	tmp = NULL;
	quotes_finder(cmd, &tmp);
	comma = commas(cmd, &tmp);
	if (comma != NULL)
		return (check_cmds_helper(cmds, cmd, tmp, comma));
	return (0);
}
