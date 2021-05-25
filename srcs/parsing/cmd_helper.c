/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 12:18:09 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/05/25 14:58:39 by abiari           ###   ########.fr       */
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
				return (free_the_nipples(tmp, cmds, cmd_counter(comma, cmd, 0), 0));
		if (i != cmd_counter(comma, cmd, 0) - 1 && only_char(' ', cmds[i]))
			return (free_the_nipples(tmp, cmds, cmd_counter(comma, cmd, 0), 0));
	}
	if (comma)
		free(comma);
	ft_lstclear(&tmp, del_node);
	return (0);
}

int	check_pipes_helper(char **cmds, char *cmd, t_list *tmp, int *pipe)
{
	int	last;
	int	i;

	i = -1;
	last = last_char(pipe);
	while (cmds[++i])
	{
		if (i == cmd_counter(pipe, cmd, 1) - 1)
			if (only_char(' ', cmds[i])
				&& (pipe[last - 1] == (int)ft_strlen(cmd) - 1))
				return (free_the_nipples(tmp, cmds, cmd_counter(pipe, cmd, 1), 1));
		if (i != cmd_counter(pipe, cmd, 1) - 1 && only_char(' ', cmds[i]))
			return (free_the_nipples(tmp, cmds, cmd_counter(pipe, cmd, 1), 1));
	}
	if (pipe)
		free(pipe);
	ft_lstclear(&tmp, del_node);
	return (0);
}

int	check_cmds(char **cmds, char *cmd)
{
	int		*comma;
	t_list	*tmp;
	int		ret;

	tmp = NULL;
	ret = quotes_finder(cmd, &tmp);
	comma = commas(cmd, &tmp);
	if (comma != NULL)
		return (check_cmds_helper(cmds, cmd, tmp, comma));
	return (0);
}
