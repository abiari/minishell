/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 17:35:24 by abiari            #+#    #+#             */
/*   Updated: 2021/05/20 10:42:39 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	spawn_proc(int in, int out, t_pipeline *cmd, char *envp[])
{
	g_vars.pid = fork();
	if (g_vars.pid == 0)
	{
		if (in != 0)
		{
			dup2(in, STDIN_FILENO);
			close(in);
		}
		if (out != 1)
		{
			dup2(out, STDOUT_FILENO);
			close(out);
		}
		redirect(cmd);
		execve(cmd->cmd[0], (char *const *)cmd->cmd, envp);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		exit(errno);
	}
}

int	fork_pipes(t_pipeline *cmd, char **envp)
{
	int		in;
	int		fd[2];
	int		status;

	in = 0;
	status = 0;
	while (cmd->next != NULL)
	{
		pipe(fd);
		spawn_proc(in, fd[1], cmd, envp);
		close(fd[1]);
		if (in != 0)
			close(in);
		in = fd[0];
		cmd = cmd->next;
	}
	if (in != STDIN_FILENO)
		close(in);
	g_vars.pid = fork();
	if (g_vars.pid == 0)
	{
		if (in != 0)
		{
			dup2(in, STDIN_FILENO);
			close(in);
		}
		redirect(cmd);
		execve(cmd->cmd[0], (char *const *)cmd->cmd, envp);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		exit(errno);
	}
	while (waitpid(-1, &status, 0) > 0)
		if (WIFEXITED(status))
			g_vars.exit_code = WEXITSTATUS(status);
	return (0);
}
