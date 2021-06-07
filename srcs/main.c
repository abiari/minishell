/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 18:06:25 by abiari            #+#    #+#             */
/*   Updated: 2021/06/07 13:37:29 by abiari           ###   ########.fr       */
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


void	msh_loop(char **line, char **envp)
{
	int	n;
	t_list	*cmd;
	t_list	*envl;

	n = 1;
	envl = envp_to_envl(envp);
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
		// int i = 0;
		// while (cmd)
		// {
		// 	while (((t_cmd *)cmd->content)->pipes)
		// 	{
		// 		i = 0;
		// 		while (((t_cmd *)cmd->content)->pipes->cmd[i])
		// 		{
		// 			printf("%s\n", ((t_cmd *)cmd->content)->pipes->cmd[i]);
		// 			if (((t_cmd *)cmd->content)->pipes->has_red)
		// 			{
		// 				while (((t_cmd *)cmd->content)->pipes->redirections)
		// 				{
		// 					printf("%s\n", ((t_cmd *)cmd->content)->pipes->redirections->file);
		// 					((t_cmd *)cmd->content)->pipes->redirections = ((t_cmd *)cmd->content)->pipes->redirections->next;
		// 				}
		// 			}
		// 			i++;
		// 		}
		// 		((t_cmd *)cmd->content)->pipes = ((t_cmd *)cmd->content)->pipes->next;
		// 	}

		// 	cmd = cmd->next;
		// }
		while (cmd != NULL)
		{
			exec(((t_cmd *)cmd->content)->pipes, &envl);
			cmd = cmd->next;
		}
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
