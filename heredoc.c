/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 15:26:14 by abiari            #+#    #+#             */
/*   Updated: 2021/08/28 15:07:17 by abiari           ###   ########.fr       */
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

void	heredoc_helper(char *stop_value, int *in)
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
	file = open(filename, O_RDONLY);
	unlink(filename);
	free(filename);
	*in = file;
}
