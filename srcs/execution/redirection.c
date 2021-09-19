/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 14:10:26 by abiari            #+#    #+#             */
/*   Updated: 2021/09/19 08:56:44 by abiari           ###   ########.fr       */
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
		else if (files->type == OUT_R)
			fd = open(files->file, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR
					| S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		else
			fd = open(files->file, O_RDONLY);
		if (fd < 0)
			print_error(files->file);
		if (files->type == DOC_R)
			unlink(files->file);
		close(fd);
		files_dup = files;
		files = files->next;
	}
}

void	infile_treat(t_redirect *red, int *doc_count, int *fd)
{
	*fd = open(red->file, O_RDONLY);
	if (*fd == -1)
		print_error(red->file);
	if (red->type == DOC_R)
	{
		unlink(red->file);
		if ((*doc_count)-- > 1)
			close(*fd);
	}
}

void	in_redirect(t_redirect *red)
{
	t_redirect	*tmp;
	int			fd;
	int			doc_count;

	tmp = red;
	fd = -1;
	doc_count = heredoc_count(red);
	while (tmp)
	{
		if (fd > 2 && tmp->type == IN_R)
			close(fd);
		if (tmp->type == IN_R || tmp->type == DOC_R)
			infile_treat(tmp, &doc_count, &fd);
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
	out_redirect(cmd->redirections);
	in_redirect(cmd->redirections);
}
