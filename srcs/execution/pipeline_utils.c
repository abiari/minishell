/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 08:45:11 by abiari            #+#    #+#             */
/*   Updated: 2021/09/19 08:46:39 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_if_dir(t_pipeline *cmd)
{
	if (is_dir(cmd->cmd[0]))
	{
		ft_putstr_fd("msh: ", 2);
		ft_putstr_fd(cmd->cmd[0], 2);
		ft_putstr_fd(": is a directory\n", 2);
		exit(126);
	}
}

void	wait_exec(void)
{
	int	status;

	status = 0;
	while (waitpid(-1, &status, 0) > 0)
		if (WIFEXITED(status))
			g_vars.exit_code = WEXITSTATUS(status);
}

int	files_in_pipe(t_pipeline **cmd, int *in, int *fd)
{
	if (((*cmd)->cmd[0][0] == '\0') && ((*cmd)->has_red == 1))
	{
		pipe(fd);
		*in = fd[0];
		close(fd[1]);
		create_file((*cmd));
		(*cmd) = (*cmd)->next;
		return (1);
	}
	return (0);
}

void	print_error(char *file)
{
	ft_putstr_fd("msh: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	exit(1);
}
