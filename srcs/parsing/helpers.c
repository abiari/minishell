/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 12:20:17 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/04/14 12:38:55 by ael-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_between_quotes(int i, t_list **lst)
{
	t_list	*tmp;

	tmp = *lst;
	while (tmp != NULL)
	{
		if (i > ((t_quotes *)tmp->content)->opens
			&& i < ((t_quotes *)tmp->content)->closes)
			return (((t_quotes *)tmp->content)->type);
		tmp = tmp->next;
	}
	return (0);
}
