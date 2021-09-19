/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 13:22:08 by abiari            #+#    #+#             */
/*   Updated: 2021/09/19 09:10:47 by abiari           ###   ########.fr       */
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
		if (!ft_isdigit(num[i]) && !(num[i] == '-' && i == 0))
			return (0);
		i++;
	}
	return (1);
}

void	exit_code(char *exit_code)
{
	char		*str_code;
	long long	code;

	code = 0;
	code = ft_ll_atoi(exit_code);
	str_code = ft_ll_itoa(code);
	if (ft_isnum(exit_code) == 0 || ft_strcmp(exit_code, str_code))
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("msh: exit: ", 2);
		ft_putstr_fd(exit_code, 2);
		ft_putstr_fd(": numeric argument required", 2);
		exit(255);
	}
	ft_putstr_fd("exit\n", 2);
	exit(code);
}

int	msh_exit(char **argv, t_list **envl)
{
	int			i;

	(void)envl;
	i = 0;
	while (argv[i] != NULL)
		i++;
	if (i >= 2)
	{
		if (ft_isnum(argv[0]) == 0)
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("msh: exit: ", 2);
			ft_putstr_fd(argv[0], 2);
			ft_putstr_fd(": numeric argument required", 2);
			exit(255);
		}
		ft_putendl_fd("msh: exit: too many arguments", 2);
		return (g_vars.exit_code = 1);
	}
	else if (i == 0)
		exit(0);
	else
		exit_code(argv[0]);
	return (0);
}
