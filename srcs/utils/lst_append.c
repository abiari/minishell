/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_append.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:16:28 by abiari            #+#    #+#             */
/*   Updated: 2021/03/06 18:17:53 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	lst_append(t_list **lst, void *content)
{
	t_list *current;
	t_list *new;

	if (!(*lst))
	{
		*lst = ft_lstnew(content);
		return ;
	}
	current = *lst;
	while (current->next)
		current = current->next;
	new = (t_list *)malloc(sizeof(t_list));
	current->next = new;
	new->content = content;
	new->next = NULL;
}
