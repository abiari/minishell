/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ll_itoa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 11:36:40 by abiari            #+#    #+#             */
/*   Updated: 2021/08/29 11:25:53 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_zero(void)
{
	char	*ret;

	ret = (char *)malloc(2);
	ret[0] = '0';
	ret[1] = '\0';
	return (ret);
}

int	ft_len(unsigned long long n)
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

int	ft_neg(unsigned long long *tmp, long long n)
{
	if (n < 0)
	{
		*tmp = -n;
		return (1);
	}
	*tmp = (unsigned long long)n;
	return (0);
}

char	*ft_ll_itoa(long long n)
{
	int					len;
	int					signe;
	unsigned long long	tmp;
	char				*ret;

	len = 0;
	signe = 0;
	tmp = n;
	if (n == 0)
		return (ret = ft_zero());
	else
		signe = ft_neg(&tmp, n);
	len = ft_len(tmp);
	ret = (char *)malloc(len + signe + 1);
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
