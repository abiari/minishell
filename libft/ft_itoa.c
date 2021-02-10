/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moerradi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 23:54:33 by moerradi          #+#    #+#             */
/*   Updated: 2019/10/10 18:25:01 by moerradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_numlen(int n)
{
	size_t len;

	len = 0;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char			*ft_itoa(int n)
{
	char			*out;
	size_t			numlen;
	size_t			i;
	unsigned int	ntemp;

	ntemp = (n > 0) ? n : n * -1;
	i = 0;
	numlen = (n > 0) ? ft_numlen(n) : ft_numlen(n) + 1;
	if (!(out = malloc(sizeof(char) * (numlen + 1))))
		return (NULL);
	out[0] = (n >= 0) ? '0' : '-';
	while (ntemp)
	{
		out[numlen - i - 1] = (ntemp % 10) + '0';
		ntemp /= 10;
		i++;
	}
	out[numlen] = '\0';
	return (out);
}
