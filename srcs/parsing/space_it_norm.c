/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_it_norm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 16:49:01 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/09/18 16:49:02 by ael-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	spaces_array(int *spaces, char *str, t_list *tmp, char c)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == c && bq(i, &tmp) == 0)
		{
			while (str[i] == c && bq(i, &tmp) == 0)
				i++;
			spaces[count] = i;
			count++;
		}
	}
	spaces[count] = -2;
}

int	spaces_count(char *str, t_list *tmp, char c)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == c && bq(i, &tmp) == 0)
		{
			while (str[i] == c && bq(i, &tmp) == 0)
				i++;
			count++;
		}
	}
	return (count);
}

char	*between_valid_spaces(char *cmd, int index, int	*space)
{
	int		i[4];
	char	*tmp;

	i[3] = last_char(space);
	i[0] = 0;
	i[2] = 0;
	if (index != i[3] - 1)
	{
		i[2] = space[index + 1] - space[index] - 1;
		i[0] = space[index];
	}
	else
	{
		i[2] = ft_strlen(cmd) - space[index];
		i[0] = space[index];
	}
	tmp = (char *)malloc((i[2] + 1) * sizeof(char));
	i[1] = -1;
	while (++i[1] < i[2])
	{
		tmp[i[1]] = cmd[i[0]];
		i[0]++;
	}
	tmp[i[2]] = '\0';
	return (tmp);
}
