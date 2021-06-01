/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 14:10:26 by abiari            #+#    #+#             */
/*   Updated: 2021/06/01 14:54:12 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	if (files_dup->type == IN_R)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (files_dup->type == OUT_R)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}
