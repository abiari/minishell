/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 18:06:25 by abiari            #+#    #+#             */
/*   Updated: 2021/05/19 11:30:50 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// t_cmds	parse_line(char *line)
// {

// }

void	msh_loop(char **line)
{
	int	n;

	n = 1;
	while (n)
	{
		g_vars.pid = 0;
		ft_putstr_fd("msh$>: ", STDOUT_FILENO);
		n = get_next_line(STDIN_FILENO, line);
		if (n == 0)
		{
			printf("exit\n");
			break ;
		}
	}
}

int		main(int ac, char *av[], char *env[])
{
	char	*line;

	(void)ac;
	(void)av;
	(void)env;
	signal(SIGQUIT, sig_handler);
	signal(SIGINT, sig_handler);
	msh_loop(&line);
	return (0);
}
