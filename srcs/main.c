/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 18:06:25 by abiari            #+#    #+#             */
/*   Updated: 2021/03/20 10:31:14 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	msh_loop(int status, char **line)
{
	char	**cmd;
	while (status)
	{
		ft_putstr_fd("msh$>: ", STDOUT_FILENO);
		get_next_line(STDIN_FILENO, line);
		cmd = parse_line(*line);
		
	}
}

int		main(int ac, char *av[], char *env[])
{
	char	*line;

	(void)ac;
	(void)av;
	(void)env;
	// signal(SIGINT, SIG_DFL);
	// signal(EOF, SIG_IGN);
	g_status = 1;
	msh_loop(g_status, &line);
	return (0);
}
