/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 14:10:26 by abiari            #+#    #+#             */
/*   Updated: 2021/05/06 14:52:55 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redirect(int in, int out, t_cmd *cmd)
{
	t_redirect	*files;
	int			fd;

	files = cmd->pipes->redirections;

	while (files->next)
	{
		if (files->type == APP_R)
			fd = open(files->fd, O_CREAT | O_APPEND | O_RDWR | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		else
			fd = open(files->fd, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR |
			S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		if (fd < 0)
		{
			ft_putstr_fd(strerror(errno), 2);
			return (1);
		}
		files = files->next;
	}
	if (files->type == IN_R)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (files->type == OUT_R)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (files->type == APP_R)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else
		/*Not a valid Type*/;

	//TODO :check IN/OUT red when inside a pipeline
}
