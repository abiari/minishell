/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 16:09:04 by abiari            #+#    #+#             */
/*   Updated: 2021/09/10 16:09:23 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_set(char c, const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, const char *set)
{
	size_t	begin;
	size_t	end;
	size_t	len;
	char	*s2;

	begin = 0;
	if (set == NULL)
		return ((char *)s1);
	if (s1 == NULL)
		return (NULL);
	while (s1[begin] != '\0' && ft_set(s1[begin], set))
		begin++;
	end = ft_strlen((char *)s1);
	while (begin < end && ft_set(s1[end - 1], set))
		end--;
	len = end - begin;
	s2 = ft_substr(s1, begin, len);
	if (!s2)
		return (NULL);
	free((void *)s1);
	return (s2);
}
