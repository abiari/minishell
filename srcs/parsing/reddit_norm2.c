/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reddit_norm2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 16:32:55 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/09/18 16:32:56 by ael-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	*reds(char *str, t_list **lst)
{
	int		count;
	int		*reds;
	t_list	*tmp;

	tmp = *lst;
	count = red_counter(str, tmp);
	if (count == 0)
		return (NULL);
	reds = malloc((sizeof(int) * count) + sizeof(int));
	if (!reds)
		return (NULL);
	red_array(reds, str, tmp);
	return (reds);
}

t_red	*norm_red(int count, int i, char *str)
{
	t_red	*red;

	red = malloc(sizeof(t_red));
	red->index = i;
	red->type = red_type_check(str, i);
	red->id = count;
	return (red);
}

int	norm_err(void)
{
	ft_putstr_fd("syntax error near `>'\n", 2);
	return (-1);
}

int	red_finder(char *str, t_list **redi, t_list **tp)
{
	int			i[2];
	t_red		*red;
	t_list		*tmp;

	tmp = *tp;
	i[0] = -1;
	i[1] = 0;
	while (str[++i[0]])
	{
		if (str[i[0]] == '>' || str[i[0]] == '<')
		{
			if (validate_red(str, i[0], tmp) == 1
				|| validate_red(str, i[0], tmp) == 2)
			{
				red = norm_red(i[1], i[0], str);
				i[1]++;
				if (validate_red(str, i[0], tmp) == 2)
					i[0]++;
				lst_append(redi, red);
			}
			else
				return (norm_err());
		}
	}
	return (i[1]);
}

int	red_type(t_list **red, int id)
{
	t_list	*reds;

	reds = *red;
	while (reds)
	{
		if (((t_red *)reds->content)->id == id - 1)
			return (((t_red *)reds->content)->type);
		reds = reds->next;
	}
	return (0);
}
