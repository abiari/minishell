/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 13:22:15 by abiari            #+#    #+#             */
/*   Updated: 2021/06/23 11:03:00 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	msh_echo(char **args, t_list *envl)
{
	int		i;

	(void)envl;
	i = 0;
	if (args[0] == NULL)
		write(1, "\n", 1);
	else
	{
		if (ft_strcmp(args[0], "-n") == 0)
			i = 1;
		while (args[i])
		{
			if (args[i][0] != '\0')
				ft_putstr_fd(args[i], 1);
			if (args[i + 1] != NULL && args[i + 1][0] != '\0')
				write(1, " ", 1);
			i++;
		}
		if (ft_strcmp(args[0], "-n") != 0)
			write(1, "\n", 1);
	}
	return (0);
}
