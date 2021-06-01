/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 13:22:15 by abiari            #+#    #+#             */
/*   Updated: 2021/05/24 10:12:13 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	msh_echo(char **args)
{
	int		i;
	t_envl	*var;

	i = 0;
	if (ft_strcmp(args[0], "-n") == 0)
		i = 1;
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1] != NULL)
			write(1, ' ', 1);
		i++;
	}
	if (ft_strcmp(args[0], "-n") != 0)
		write(1, '\n', 1);
	return (0);
}
