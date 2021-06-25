/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 14:10:26 by abiari            #+#    #+#             */
/*   Updated: 2021/06/25 09:29:42 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	heredoc(char *stop_value, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (*line == '\0')
			*line = '\n';
		if (!line)
		{
			free(line);
			line = NULL;
			break ;
		}
		if (!ft_strcmp(line, stop_value))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
}

void	heredoc_helper(char *stop_value, int *in)
{
	int	file;

	file = open("/tmp/heredoctmpfile", O_CREAT | O_TRUNC | O_WRONLY,
			S_IRGRP | S_IWGRP | S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH);
	if (file < 0)
	{
		ft_putstr_fd(strerror(errno), 2);
		write(2, "\n", 1);
		exit(errno);
	}
	heredoc(stop_value, file);
	close(file);
	file = open("/tmp/heredoctmpfile", O_RDONLY);
	unlink("/tmp/heredoctmpfile");
	*in = file;
}

void	create_file(t_pipeline *cmd)
{
	t_redirect	*files;
	t_redirect	*files_dup;
	int			fd;

	files = cmd->redirections;
	while (files)
	{
		if (files->type == APP_R)
			fd = open(files->file, O_CREAT | O_APPEND | O_WRONLY, S_IRUSR
					| S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		else if (files->type == IN_R)
			fd = open(files->file, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR
					| S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		else if (files->type == DOC_R)
			heredoc_helper(files->file, &fd);
		else
			fd = open(files->file, O_RDONLY);
		if (fd < 0)
		{
			ft_putstr_fd(strerror(errno), 2);
			write(2, "\n", 1);
			exit(errno);
		}
		close(fd);
		files_dup = files;
		files = files->next;
	}
}

void	redirect(t_pipeline *cmd)
{
	t_redirect	*files;
	t_redirect	*files_dup;
	int			fd;

	files = cmd->redirections;
	while (files)
	{
		if (files->type == APP_R)
			fd = open(files->file, O_CREAT | O_APPEND | O_WRONLY, S_IRUSR
					| S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		else if (files->type == IN_R)
			fd = open(files->file, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR
					| S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		else if (files->type == DOC_R)
			heredoc_helper(files->file, &fd);
		else
			fd = open(files->file, O_RDONLY);
		if (fd < 0)
		{
			ft_putstr_fd(strerror(errno), 2);
			write(2, "\n", 1);
			exit(errno);
		}
		files_dup = files;
		files = files->next;
	}
	if (files_dup->type == IN_R && fd > 2)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (files_dup->type == OUT_R && fd > 2)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (files_dup->type == DOC_R && fd > 2)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else
	{
		if (fd > 2)
		{
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
	}
}
