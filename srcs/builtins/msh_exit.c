/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 13:22:08 by abiari            #+#    #+#             */
/*   Updated: 2021/05/22 15:43:39 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

long long	ft_ll_atoi(const char *ptr)
{
	long long	res;
	int			sign;
	int			i;

	res = 0;
	sign = 1;
	i = 0;
	while ((ptr[i] >= 9 && ptr[i] <= 13) || ptr[i] == ' ')
		i++;
	if (ptr[i] == '+' || ptr[i] == '-')
	{
		if (ptr[i] == '-')
			sign = -1;
		i++;
	}
	while (ptr[i] && ptr[i] >= '0' && ptr[i] <= '9')
	{
		res = res * 10 + (ptr[i] - '0');
		i++;
	}
	return (res * sign);
}

int	msh_exit(char **argv)
{
	int	i;
	int	code;

	i = 0;
	code = 0;
	while (argv[i] != NULL)
		i++;
	if (i > 2)
	{
		ft_putstr_fd("msh: exit: too many arguments", 2);
		return (g_vars.exit_code = 1);
	}
	else
	{
		i = 0;
		while (argv[0][i] != NULL)
		{
			if (ft_isdigit(argv[i]) == 0)
			{
				printf("exit \n");
				ft_putstr_fd("msh: exit: ", 2);
				ft_putstr_fd(argv[0], 2);
				ft_putstr_fd(": numeric argument required", 2);
				exit(255);
			}
		}
		code = ft_ll_atoi(argv[0]);
		printf("exit\n");
		if (code > 255)
			exit(code % 256);
		else if (code < 0)
			exit(code % 256 + 256);
		else
			exit(code);
	}
}
