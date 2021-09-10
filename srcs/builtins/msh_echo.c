/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 13:22:15 by abiari            #+#    #+#             */
/*   Updated: 2021/09/09 13:56:23 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	msh_echo(char **args, t_list **envl)
{
	int		i;
	int		j;
	int		flag;

	(void)envl;
	i = 0;
	flag = 0;
	if (args[0] == NULL)
		write(1, "\n", 1);
	else
	{
		while (args[i][0] == '-' && args[i][1] == 'n')
		{
			j = 2;
			while (args[i][j])
			{
				if (args[i][j] != 'n')
				{
					j = -1;
					break ;
				}
				j++;
			}
			if (j == -1)
				break ;
			flag = 1;
			i++;
		}
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
