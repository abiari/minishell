/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 18:15:04 by abiari            #+#    #+#             */
/*   Updated: 2021/03/17 11:21:17 by ael-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*str;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(src);
	if ((str = (char*)malloc(len + 1)) == NULL)
		return (NULL);
	while (i < len)
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strdup_dzeb(char *src)
{
	char	*str;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(src);
	if ((str = (char*)malloc(len + 1)) == NULL)
		return (NULL);
	while (i < len)
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	free(src);
	return (str);
}
