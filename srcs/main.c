/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 18:06:25 by abiari            #+#    #+#             */
/*   Updated: 2021/09/09 14:59:53 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_globals	g_vars;

void	msh_loop(char **line, t_list *envl)
{
	t_list	*cmd;

	while (1)
	{
		*line = readline("\033[0;36mmsh$:\033[0m ");
		if (!(*line))
		{
			if (isatty(0))
				printf("exit\n");
			free(*line);
			*line = NULL;
			exit(g_vars.exit_code);
		}
		if (**line == '\0')
		{
			free(*line);
			*line = NULL;
			continue ;
		}
		add_history(*line);
		cmd = main_lst(*line, &envl);
		if (cmd != NULL)
		{
			heredoc_spawn(((t_cmd *)cmd->content)->pipes);
			exec(((t_cmd *)cmd->content)->pipes, &envl);
			free(*line);
			*line = NULL;
			if (!isatty(0))
				exit(0);
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
