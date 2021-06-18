/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 13:38:03 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/06/15 15:35:39 by ael-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*fill_red(char *cmd, int index, int *array)
{
	int		i;
	int		j;
	int		len;
	int		last;
	char	*tmp;

	last = last_char(array);
	len = red_len_init(index, array, last, cmd);
	i = red_i_init(index, array, last, cmd);
	j = 0;
	tmp = (char *)malloc((len + 1) * sizeof(char));
	while (j < len)
	{
		tmp[j] = cmd[i];
		i++;
		j++;
	}
	tmp[len] = '\0';
	return (tmp);
}

int	red_len_init(int index, int *array, int last, char *cmd)
{
	int prev;
	int len;

	len = 0;
	prev = 0;
	if (index == 0)
		return (array[index]);
	if (red_type_check(cmd, array[index - 1]) == APP_R || red_type_check(cmd, array[index - 1]) == DOC_R)
		prev = 1;
	if(index == last)
	{
		len = ft_strlen(cmd) - array[index - 1] - 1;
		return (len);
	}
	else
		return (array[index] - array[index - 1] - 1 - prev);

}

int	red_i_init(int index, int *array, int last, char *cmd)
{
	int prev;

	prev = 0;
	if (index == 0)
		return (0);
	if (red_type_check(cmd, array[index - 1]) == APP_R || red_type_check(cmd, array[index - 1]) == DOC_R)
		prev = 1;
	if (index == last)
		return (array[index - 1] + 1 + prev);
	else
		return (array[index - 1] + 1 + prev);

}
