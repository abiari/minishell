/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commas_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 11:46:06 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/04/14 12:45:19 by ael-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	commas_counter(char *str, t_list *tmp)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == '\\' && (i++))
			continue ;
		if (str[i] == ';' && is_between_quotes(i, &tmp) == 0)
			count++;
	}
	return (count);
}

void	commas_array(int *commas, char *str, t_list *tmp)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == '\\' && (i++))
			continue ;
		if (str[i] == ';' && is_between_quotes(i, &tmp) == 0)
		{
			commas[count] = i;
			count++;
		}
	}
	commas[count] = -2;
}

int	*commas(char *str, t_list **lst)
{
	int		count;
	int		*commas;
	t_list	*tmp;

	tmp = *lst;
	count = commas_counter(str, tmp);
	if (count == 0)
		return (NULL);
	commas = malloc((sizeof(int) * count) + sizeof(int));
	if (!commas)
		return (NULL);
	commas_array(commas, str, tmp);
	return (commas);
}

int	check_last_cmd(char *cmd, int last_comma)
{
	int	i;
	int	flag;

	i = last_comma;
	flag = 0;
	while (cmd[i])
		i++;
	if (i == last_comma + 1)
		return (0);
	return (1);
}

int	last_comma(int *commas)
{
	int	last;

	last = 0;
	while (commas[last] != -2)
		last++;
	return (last);
}
