/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 13:22:15 by abiari            #+#    #+#             */
/*   Updated: 2021/09/08 16:16:50 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	msh_echo(char **args, t_list **envl)
{
	int		i;

	(void)envl;
	i = 0;
	if (args[0] == NULL)
		write(1, "\n", 1);
	else
	{
		while (ft_strcmp(args[i], "-n") == 0)
			i++;
		while (args[i])
		{
			ft_putstr_fd(args[i], 1);
			if (args[i + 1] != NULL)
				write(1, " ", 1);
			i++;
		}
		if (ft_strcmp(args[0], "-n") != 0)
			write(1, "\n", 1);
	}
	return (0);
}
