/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 18:57:09 by abiari            #+#    #+#             */
/*   Updated: 2019/10/15 10:40:13 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*strnew;
	unsigned int	i;

	i = 0;
	if (!s || !(strnew = (char*)malloc(ft_strlen((char*)s) + 1)))
		return (NULL);
	while (s[i] != 0)
	{
		strnew[i] = (*f)(i, s[i]);
		i++;
	}
	strnew[i] = '\0';
	return (strnew);
}
