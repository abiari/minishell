/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 14:10:26 by abiari            #+#    #+#             */
/*   Updated: 2021/06/26 12:06:02 by abiari           ###   ########.fr       */
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
	t_redirect	*in;
	t_redirect	*out;
	int			in_fd;
	int			out_fd;

	in_fd = 0;
	out_fd = 1;
	files = cmd->redirections;
	while (files)
	{
		if (files->type == APP_R)
		{
			if (out_fd != 1)
				close(out_fd);
			out_fd = open(files->file, O_CREAT | O_APPEND | O_WRONLY, S_IRUSR
					| S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		}
		else if (files->type == IN_R)
		{
			if (out_fd != 1)
				close(out_fd);
			out_fd = open(files->file, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR
					| S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		}
		else if (files->type == DOC_R)
		{
			if (in_fd != 0)
				close(in_fd);
			heredoc_helper(files->file, &in_fd);
		}
		else
		{
			if (in_fd != 0)
				close(in_fd);
			in_fd = open(files->file, O_RDONLY);
		}
		if (in_fd < 0 || out_fd < 0)
		{
			ft_putstr_fd(strerror(errno), 2);
			write(2, "\n", 1);
			exit(errno);
		}
		if (files->type == DOC_R || files->type == OUT_R)
			in = files;
		if (files->type == APP_R || files->type == IN_R)
			out = files;
		files = files->next;
	}
	if (out->type == IN_R && out_fd > 2)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
	else
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
	if (in->type == OUT_R && in_fd > 2)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	else
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
}
