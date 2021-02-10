/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerradi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 12:01:36 by moerradi          #+#    #+#             */
/*   Updated: 2019/10/09 23:44:12 by moerradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t				i;
	const unsigned char	*tempsrc;
	unsigned char		*tempdst;

	i = 0;
	tempsrc = (unsigned char*)src;
	tempdst = (unsigned char*)dst;
	while (i < n)
	{
		if ((*tempdst++ = *tempsrc++) == (unsigned char)c)
			return (tempdst);
		i++;
	}
	return (NULL);
}
