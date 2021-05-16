/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 17:35:24 by abiari            #+#    #+#             */
/*   Updated: 2021/05/16 17:23:04 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int spawn_proc(int in, int out, t_pipeline *cmd, char *envp[])
{
	pid_t pid;

	if ((pid = fork()) == 0)
	{
		if (in != 0)
		{
			dup2(in, 0);
			close(in);
		}
		if (out != 1)
		{
			dup2(out, 1);
			close(out);
		}
		return execve(cmd->cmd[0], (char *const *)cmd->cmd, envp);
	}
	return pid;
}

int	fork_pipes(t_pipeline *cmd, char **envp)
{
	int		in;
	int		fd[2];
	pid_t	pid;
	int		ret = 0;

	in = 0;
	while (cmd->next != NULL)
	{
		pipe(fd);
		spawn_proc(in, fd[1], cmd, envp);
		close(fd[1]);
		if (in != 0)
		{
			dup2(in, 0);
			close(in);
		}
		in = fd[0];
		cmd = cmd->next;
	}
	if (in != 0)
	{
		dup2(in, 0);
		close(in);
	}
	pid = fork();
	if (pid == 0)
		execve(cmd->cmd[0], (char *const *)cmd->cmd, envp);
	// while (wait(NULL) != -1);
	while (waitpid(-1, &ret, 0) != -1);
		//printf("%d\n", WEXITSTATUS(ret));
	return (ret);
}

void	error()
{
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	exit(-1);
}
