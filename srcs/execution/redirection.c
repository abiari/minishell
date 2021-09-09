/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 14:10:26 by abiari            #+#    #+#             */
/*   Updated: 2021/09/08 16:15:09 by abiari           ###   ########.fr       */
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
		close(fd);
		files_dup = files;
		files = files->next;
	}
}

void	in_redirect(t_redirect *red)
{
	t_redirect	*tmp;
	int			fd;

	tmp = red;
	fd = -1;
	while (tmp)
	{
		if (fd > 2 && (tmp->type == IN_R || tmp->type == DOC_R))
			close(fd);
		if (tmp->type == IN_R || tmp->type == DOC_R)
		{
			fd = open(tmp->file, O_RDONLY);
			if (fd == -1)
			{	
				ft_putstr_fd("msh: ", 2);
				ft_putstr_fd(tmp->file, 2);
				ft_putstr_fd(": ", 2);
				ft_putendl_fd(strerror(errno), 2);
				exit(1);
			}
		}
		tmp = tmp->next;
	}
	if (fd > 2)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}

void	out_redirect(t_redirect *red)
{
	t_redirect	*tmp;
	int			fd;

	tmp = red;
	fd = -1;
	while (tmp)
	{
		if (fd > 2 && (tmp->type == OUT_R || tmp->type == APP_R))
			close(fd);
		if (tmp->type == OUT_R)
			fd = open(tmp->file, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR
					| S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		if (tmp->type == APP_R)
			fd = open(tmp->file, O_CREAT | O_APPEND | O_WRONLY, S_IRUSR
					| S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		tmp = tmp->next;
	}
	if (fd > 2)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

void	redirect(t_pipeline *cmd)
{
	in_redirect(cmd->redirections);
	out_redirect(cmd->redirections);
}
