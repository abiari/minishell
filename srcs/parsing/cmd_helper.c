/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 12:18:09 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/09/17 13:42:03 by ael-bagh         ###   ########.fr       */
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

int	free_pipes(int *p, t_list *t, char **c, int tmp)
{
	free(p);
	return (free_them(t, c, tmp, 1));
}

int	check_pipes_helper(char **c, char *cmd, t_list *t, int *p)
{
	int	tmp[4];

	tmp[0] = last_char(p);
	tmp[1] = -1;
	tmp[3] = cmd_counter(p, cmd, 1);
	while (c[++tmp[1]])
	{
		if (tmp[1] == tmp[3] - 1)
		{
			if (only_char(' ', c[tmp[1]])
				|| (p[tmp[0] - 1] == (int)ft_strlen(cmd) - 1))
			{
				return (free_pipes(p, t, c, tmp[3]));
			}
		}
		if (tmp[1] != tmp[3] - 1 && only_char(' ', c[tmp[1]]))
			return (free_pipes(p, t, c, tmp[3]));
	}
	if (p)
		free(p);
	ft_lstclear(&t, del_node);
	return (0);
}
