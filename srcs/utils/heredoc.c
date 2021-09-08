/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 15:26:14 by abiari            #+#    #+#             */
/*   Updated: 2021/09/08 11:55:15 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	heredoc(char *stop_value, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			free(line);
			line = NULL;
			break ;
		}
		if (*line == '\0')
			*line = '\n';
		if (!ft_strcmp(line, stop_value))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		if (*line != '\n')
			write(fd, "\n", 1);
		free(line);
	}
}

char 	*heredoc_helper(char *stop_value)
{
	int		file;
	char	*filename;

	filename = rand_str();
	file = open(filename, O_CREAT | O_TRUNC | O_WRONLY,
			S_IRGRP | S_IWGRP | S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH);
	if (file < 0)
	{
		free(filename);
		ft_putstr_fd(strerror(errno), 2);
		write(2, "\n", 1);
		exit(errno);
	}
	heredoc(stop_value, file);
	close(file);
	return (filename);
}

int		heredoc_count(t_redirect *reds)
{
	int count;

	count = 0;
	while (reds)
	{
		if (reds->type == DOC_R)
			count++;
		reds = reds->next;
	}
	return (count);
}

void	heredoc_spawn(t_pipeline *cmd)
{
	char		*filename;
	char		*tmp;
	t_pipeline	*cmd_tmp;
	t_redirect	*reds_tmp;
	int			reds_count;

	if (!cmd->redirections)
		return;
	cmd_tmp = cmd;
	while (cmd_tmp)
	{
		if (cmd_tmp->has_red)
		{
			reds_tmp = cmd_tmp->redirections;
			reds_count = heredoc_count(cmd_tmp->redirections);
			while (reds_tmp && reds_count)
			{
				if (reds_tmp->type == DOC_R)
				{
					tmp = reds_tmp->file; 
					filename = heredoc_helper(reds_tmp->file);
					reds_tmp->file = filename;
					free(tmp);
					reds_tmp = reds_tmp->next;
					reds_count--;
				}
			}
		}
		cmd_tmp = cmd_tmp->next;
	}
}
