/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 13:22:08 by abiari            #+#    #+#             */
/*   Updated: 2021/06/07 11:12:38 by abiari           ###   ########.fr       */
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

int	ft_isnum(char *num)
{
	int	i;

	i = 0;
	while (num[i])
	{
		if (!ft_isdigit(num[i]))
			return (0);
		i++;
	}
	return (1);
}

int	msh_exit(char **argv, t_list *envl)
{
	int	i;
	int	code;

	(void)envl;
	i = 0;
	code = 0;
	while (argv[i] != NULL)
		i++;
	if (i > 2)
	{
		ft_putstr_fd("msh: exit: too many arguments", 2);
		return (g_vars.exit_code = 1);
	}
	else if (i == 0)
		exit(0);
	else
	{
		i = 0;
		// while (argv[0][i] != '\0')
		// {
		if (ft_isnum(argv[i]) == 0)
		{
			printf("exit \n");
			ft_putstr_fd("msh: exit: ", 2);
			ft_putstr_fd(argv[0], 2);
			ft_putstr_fd(": numeric argument required", 2);
			exit(255);
		}
		// }
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
