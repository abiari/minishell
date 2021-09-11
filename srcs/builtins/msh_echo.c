/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 13:22:15 by abiari            #+#    #+#             */
/*   Updated: 2021/09/11 09:48:26 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_option(int *i, int *flag, char **args)
{
	int	j;

	while (args[*i][0] == '-' && args[*i][1] == 'n')
	{
		j = 2;
		while (args[*i][j])
		{
			if (args[*i][j] != 'n')
			{
				j = -1;
				break ;
			}
			j++;
		}
		if (j == -1)
			break ;
		*flag = 1;
		(*i)++;
	}
}

int	msh_echo(char **args, t_list **envl)
{
	int		i;
	int		flag;

	(void)envl;
	i = 0;
	flag = 0;
	if (args[0] == NULL)
		write(1, "\n", 1);
	else
	{
		check_option(&i, &flag, args);
		while (args[i])
		{
			ft_putstr_fd(args[i], 1);
			if (args[i + 1] != NULL)
				write(1, " ", 1);
			i++;
		}
		if (flag != 1)
			write(1, "\n", 1);
	}
	return (0);
}
