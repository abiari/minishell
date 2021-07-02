/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 18:06:25 by abiari            #+#    #+#             */
/*   Updated: 2021/07/02 12:57:33 by abiari           ###   ########.fr       */
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
			exit(g_vars.exit_code);
		}
		if (**line == '\0')
		{
			free(*line);
			*line = NULL;
			continue ;
		}
		g_vars.exit_code = 0;
		add_history(*line);
		cmd = main_lst(*line, &envl);
		if (cmd != NULL)
		{
			/*mini parser for heredoc*/
			mod_env_var("_", *line, &envl);
			exec(((t_cmd *)cmd->content)->pipes, &envl);
			free(*line);
			*line = NULL;
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
