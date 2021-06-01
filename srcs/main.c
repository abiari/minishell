/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 18:06:25 by abiari            #+#    #+#             */
/*   Updated: 2021/06/01 14:43:03 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_globals	g_vars;

void	msh_prompt(void)
{
	ft_putstr_fd("msh$: ", STDOUT_FILENO);
	ft_putstr_fd(getcwd(NULL, 0), STDOUT_FILENO);
	ft_putstr_fd(">> ", STDOUT_FILENO);
}


void	msh_loop(char **line, char **envp)
{
	int	n;
	t_list *cmd;
	// t_cmd *cmd_cast;

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
		// cmd_cast = (t_cmd *)(cmd);

		exec(((t_cmd *)cmd->content)->pipes, envp);
	}
}

int		main(int ac, char *av[], char *env[])
{
	char	*line;

	(void)ac;
	(void)av;
	signal(SIGQUIT, sig_handler);
	signal(SIGINT, sig_handler);
	msh_loop(&line, env);
	return (0);
}
