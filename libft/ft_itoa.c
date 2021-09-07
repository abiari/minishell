/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 11:36:40 by abiari            #+#    #+#             */
/*   Updated: 2021/09/07 12:10:34 by ael-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_zeroo(void)
{
	char	*ret;

	ret = (char *)malloc(2);
	ret[0] = '0';
	ret[1] = '\0';
	return (ret);
}

int	ft_len2(unsigned int n)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

int	ft_nega(unsigned int *tmp, int n)
{
	if (n < 0)
	{
		*tmp = -n;
		return (1);
	}
	*tmp = (unsigned int)n;
	return (0);
}

char	*ft_itoa(int n)
{
	int				len;
	int				signe;
	unsigned int	tmp;
	char			*ret;

	len = 0;
	signe = 0;
	tmp = n;
	if (n == 0)
		return (ret = ft_zeroo());
	else
		signe = ft_nega(&tmp, n);
	len = ft_len2(tmp);
	if (!(ret = (char *)malloc(len + signe + 1)))
		return (NULL);
	*(ret + len-- + signe) = '\0';
	while (tmp > 0)
	{
		*(ret + len + signe) = tmp % 10 + '0';
		len--;
		tmp /= 10;
	}
	if (signe)
		*ret = '-';
	return (ret);
}
