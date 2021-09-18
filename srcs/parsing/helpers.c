/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 12:20:17 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/09/18 16:43:15 by ael-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	bq(int i, t_list **lst)
{
	t_list	*tmp;

	tmp = *lst;
	if (!tmp)
		return (0);
	while (tmp != NULL)
	{
		if (i > ((t_quotes *)tmp->content)->opens
			&& i < ((t_quotes *)tmp->content)->closes)
			return (((t_quotes *)tmp->content)->type);
		tmp = tmp->next;
	}
	return (0);
}

int	is_valid_quote(int	i, t_list **lst)
{
	t_list	*tmp;

	tmp = *lst;
	while (tmp != NULL)
	{
		if (i == ((t_quotes *)tmp->content)->opens
			|| i == ((t_quotes *)tmp->content)->closes)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

char	*ft_strndup(const char *src, int n)
{
	int		i;
	char	*ret;

	i = 0;
	ret = malloc(sizeof(char) * (n + 1));
	if (!ret || !src)
		return (NULL);
	while (i < n && src)
	{
		ret[i] = src[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
