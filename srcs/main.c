/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 18:06:25 by abiari            #+#    #+#             */
/*   Updated: 2021/06/08 08:00:50 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_globals	g_vars;

void	msh_prompt(void)
{
	ft_putstr_fd("\033[0;36mmsh$:\033[0m ", STDOUT_FILENO);
	ft_putstr_fd("\033[0;35m", STDOUT_FILENO);
	ft_putstr_fd(getcwd(NULL, 0), STDOUT_FILENO);
	ft_putstr_fd("\033[0m", STDOUT_FILENO);
	ft_putstr_fd("\033[0;35m>>\033[0m ", STDOUT_FILENO);
}


void	msh_loop(char **line, t_list *envl)
{
	int		n;
	t_list	*cmd;

	n = 1;
	while (n)
	{
		msh_prompt();
		n = get_next_line(STDIN_FILENO, line);
		if (n == 0)
		{
			printf("exit\n");
			break ;
		}
		cmd = main_lst(*line);
		while (cmd != NULL)
		{
			//mini parser for each command separated by ";"
			// wait for each command to execute then pass
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
