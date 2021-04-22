/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 09:43:58 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/04/22 15:24:43 by ael-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	quote_ends(int type, int i, char *str)
{
	char	quote;

	if (type == S_QUOTE)
		quote = '\'';
	if (type == D_QUOTE)
		quote = '\"';
	while (str[i])
	{
		if (str[i] == quote)
			return (i);
		i++;
	}
	return (-1);
}

int	s_d_quote(t_quotes *quotes, t_list **lst, int i, char *str)
{
	quotes = malloc(sizeof(t_quotes));
	if (str[i] == '\'')
		quotes->type = S_QUOTE;
	if (str[i] == '\"')
		quotes->type = D_QUOTE;
	quotes->opens = i;
	quotes->closes = quote_ends(quotes->type, i + 1, str);
	if (quotes->closes == -1)
	{
		ft_lstclear(lst, del_node);
		return (-1);
	}
	lst_append(lst, quotes);
	return (0);
}

// int	d_quote(t_quotes *quotes, t_list **lst, int i, char *str)
// {
// 	quotes = malloc(sizeof(t_quotes));
// 	quotes->type = D_QUOTE;
// 	quotes->opens = i;
// 	quotes->closes = quote_ends(D_QUOTE, i + 1, str);
// 	if (quotes->closes == -1)
// 	{
// 		ft_lstclear(lst, del_node);
// 		return (-1);
// 	}
// 	lst_append(lst, quotes);
// 	return (0);
// }

void	q_helper(int *type, int *flag, int i, int *counter)
{
	if (i == 1)
	{
		*type = S_QUOTE;
		*flag = 1;
	}
	if (i == 2)
	{
		*type = D_QUOTE;
		*flag = 1;
	}
	(*counter)++;
}

int	quotes_finder(char *str, t_list **lst)
{
	int			i;
	int			counter;
	int			type;
	int			flag;
	t_quotes	*quotes;

	i = -1;
	quotes = NULL;
	counter = 0;
	while (str[++i])
	{
		flag = 0;
		if (str[i] == '\\')
		{
			i++;
			continue ;
		}
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (s_d_quote(quotes, lst, i, str) == -1)
				return (-1);
			q_helper(&type, &flag, 1 + (str[i] == '\"'), &counter);
		}
		if (flag == 1)
			i = quote_ends(type, i + 1, str);
	}
	return (counter);
}
