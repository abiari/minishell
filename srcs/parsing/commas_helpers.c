/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commas_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 11:46:06 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/06/21 13:57:32 by ael-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	char_counter(char *str, t_list *tmp, char c)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == '\\' && (i++))
			continue ;
		if (str[i] == c && is_between_quotes(i, &tmp) == 0)
			count++;
	}
	return (count);
}

void	char_array(int *array, char *str, t_list *tmp, char c)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == '\\' && (i++))
			continue ;
		if (str[i] == c && is_between_quotes(i, &tmp) == 0)
		{
			array[count] = i;
			count++;
		}
	}
	array[count] = -2;
}

int	*commas(char *str, t_list **lst)
{
	int		count;
	int		*commas;
	t_list	*tmp;

	tmp = *lst;
	count = char_counter(str, tmp, ';');
	if (count == 0)
		return (NULL);
	commas = malloc((sizeof(int) * count) + sizeof(int));
	if (!commas)
		return (NULL);
	char_array(commas, str, tmp, ';');
	return (commas);
}

int	check_last_cmd(char *cmd, int last_comma)
{
	int	i;

	i = last_comma;
	while (cmd[i])
		i++;
	if (i == last_comma + 1)
		return (0);
	return (1);
}

int	last_char(int *array)
{
	int	last;

	last = 0;
	while (array[last] != -2)
		last++;
	return (last);
}
