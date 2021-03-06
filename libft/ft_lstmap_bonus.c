/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 10:36:10 by abiari            #+#    #+#             */
/*   Updated: 2019/10/21 16:13:42 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*new;
	t_list	*newtmp;

	if (!lst || !f)
		return (NULL);
	tmp = lst;
	new = ft_lstnew(f(tmp->content));
	tmp = tmp->next;
	while (tmp != NULL)
	{
		if (!(newtmp = ft_lstnew(f(tmp->content))))
		{
			ft_lstclear(&new, del);
			new = NULL;
			break ;
		}
		ft_lstadd_back(&new, ft_lstnew(f(tmp->content)));
		tmp = tmp->next;
	}
	return (new);
}
