/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 18:06:25 by abiari            #+#    #+#             */
/*   Updated: 2021/09/15 10:25:45 by ael-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_globals	g_vars;

void	free_chard(char **str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		free(str[i]);
		i++;
	}
	free(str[i]);
	free(str);
	str = NULL;
}

void	free_mainlst(t_pipeline **lst)
{
	t_pipeline *tmp;
	t_redirect *rd;

	while(*lst)
	{
		free_chard((*lst)->cmd);
		if ((*lst)->has_red)
		{
			while((*lst)->redirections)
			{
				free((*lst)->redirections->file);
				rd = (*lst)->redirections->next;
				free((*lst)->redirections);
				(*lst)->redirections = rd;
			}
		}
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp);
	}
}

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
			free_mainlst(&(((t_cmd *)cmd->content)->pipes));
			ft_lstclear(&cmd, delist);
			if (!isatty(0))
				exit(0);
		}
		free(*line);
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
