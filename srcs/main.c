/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 18:06:25 by abiari            #+#    #+#             */
/*   Updated: 2021/06/24 08:49:07 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_globals	g_vars;

void	msh_loop(char **line, t_list *envl)
{
	int		n;
	t_list	*cmd;

	n = 1;
	while (n)
	{
		*line = readline("\033[0;36mmsh$:\033[0m ");
		if (!(*line))
		{
			printf("exit\n");
			free(*line);
			*line = NULL;
			break ;
		}
		if (**line == '\0')
		{
			free(*line);
			*line = NULL;
			continue ;
		}
		add_history(*line);
		cmd = main_lst(*line, &envl);
		while (cmd != NULL)
		{
			exec(((t_cmd *)cmd->content)->pipes, &envl);
			cmd = cmd->next;
		}
	}
}

int	main(int ac, char *av[], char *envp[])
{
	t_list	*envl;
	char	*line;

	(void)ac;
	(void)av;
	signal(SIGQUIT, sig_handler);
	signal(SIGINT, sig_handler);
	envl = envp_to_envl(envp);
	msh_loop(&line, envl);
	return (0);
}
