/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:51:15 by abiari            #+#    #+#             */
/*   Updated: 2021/03/09 18:04:09 by abiari           ###   ########.fr       */
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
