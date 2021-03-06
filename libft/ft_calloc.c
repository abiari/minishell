/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 16:40:49 by abiari            #+#    #+#             */
/*   Updated: 2019/10/19 16:23:10 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	void	*str;

	if (size == 0)
	{
		n = 1;
		size = 1;
	}
	if ((str = malloc(n * size)) == NULL)
		return (NULL);
	ft_bzero(str, n * size);
	return (str);
}
