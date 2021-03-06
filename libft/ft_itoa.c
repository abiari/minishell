/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 11:36:40 by abiari            #+#    #+#             */
/*   Updated: 2019/10/28 08:01:29 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*ft_zero(void)
{
	char	*ret;

	ret = (char *)malloc(2);
	ret[0] = '0';
	ret[1] = '\0';
	return (ret);
}

static	int		ft_len(unsigned int n)
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

static	int		ft_neg(unsigned int *tmp, int n)
{
	if (n < 0)
	{
		*tmp = -n;
		return (1);
	}
	*tmp = (unsigned int)n;
	return (0);
}

char			*ft_itoa(int n)
{
	int				len;
	int				signe;
	unsigned int	tmp;
	char			*ret;

	len = 0;
	signe = 0;
	tmp = n;
	if (n == 0)
		return (ret = ft_zero());
	else
		signe = ft_neg(&tmp, n);
	len = ft_len(tmp);
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
