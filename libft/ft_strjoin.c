/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 18:53:11 by abiari            #+#    #+#             */
/*   Updated: 2021/05/15 09:17:04 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		size;
	char	*ret;

	if (!s1)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	ret = (char *)malloc(size + 1);
	if (ret == NULL)
		return (ret);
	strncpy(ret, s1, ft_strlen(s1));
	strncpy(ret + ft_strlen(s1), s2, ft_strlen(s2));
	//ft_strlcpy(ret, s1, ft_strlen(s1));
	//ft_strlcpy(ret + ft_strlen(s1), s2, ft_strlen(s2));
	return (ret);
}
