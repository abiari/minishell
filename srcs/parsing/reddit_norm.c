/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reddit_norm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 16:31:42 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/09/18 16:43:15 by ael-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ret_count(int count, int i)
{
	if (i == 0)
	{
		if (count > 2)
			return (-1);
		if (count == 1)
			return (OUT_R);
		if (count == 2)
			return (APP_R);
	}
	else
	{
		if (count > 2)
			return (-1);
		if (count == 1)
			return (IN_R);
		if (count == 2)
			return (DOC_R);
	}
	return (-1);
}

int	red_type_check(char *str, int i)
{
	int	count;

	count = 0;
	if (str[i] == '>')
	{
		while (str[i] == '>')
		{
			i++;
			count++;
		}
		return (ret_count(count, 0));
	}
	if (str[i] == '<')
	{
		while (str[i] == '<')
		{
			i++;
			count++;
		}
		return (ret_count(count, 1));
	}
	return (-1);
}

int	validate_red(char *str, int i, t_list *tmp)
{
	int	red;

	red = red_type_check(str, i);
	if (red != -1)
	{
		if ((red == IN_R || red == OUT_R)
			&& bq(i, &tmp) == 0)
			return (1);
		else if (red == APP_R || red == DOC_R)
		{
			if (bq(i, &tmp) == 0
				&& bq(i + 1, &tmp) == 0)
				return (2);
		}
	}
	return (0);
}

int	red_counter(char *str, t_list *tmp)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == '>' || str[i] == '<')
		{
			if (validate_red(str, i, tmp) == 1)
				count++;
			else if (validate_red(str, i, tmp) == 2)
			{
				i++;
				count++;
			}
		}
	}
	return (count);
}

void	red_array(int *array, char *str, t_list *tmp)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == '>' || str[i] == '<')
		{
			if (validate_red(str, i, tmp) == 1)
			{
				array[count] = i;
				count++;
			}
			if (validate_red(str, i, tmp) == 2)
			{
				array[count] = i;
				count++;
				i++;
			}
		}
	}
	array[count] = -2;
}
