/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:51:15 by abiari            #+#    #+#             */
/*   Updated: 2019/10/15 11:57:38 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;
	void	*data;

	data = content;
	if (!(new = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	new->content = data;
	new->next = NULL;
	return (new);
}
