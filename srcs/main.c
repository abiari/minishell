/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 18:06:25 by abiari            #+#    #+#             */
/*   Updated: 2021/02/21 15:08:03 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmds	parse_line(char *line)
{
	
}

void	msh_loop(int status, char **line)
{
	while (status)
	{
		ft_putstr_fd("msh$>: ", STDIN_FILENO);
		get_next_line(STDIN_FILENO, line);
	}
}

int		main(int ac, char *av[], char *env[])
{
	char	*line;

	(void)ac;
	(void)av;
	(void)env;
	g_status = 1;
	msh_loop(g_status, &line);
	return (0);
}