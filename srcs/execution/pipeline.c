/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 17:35:24 by abiari            #+#    #+#             */
/*   Updated: 2021/06/07 13:47:46 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*check_exec(char *cmd, t_list *envl)
{
	char	*bin;
	int		fd;

	bin = cmd;
	fd = open(bin, O_RDONLY);
	if (fd < 0)
	{
		bin = bin_path(bin, envl);
		close(fd);
	}
	return (bin);
}

void	spawn_proc(int in, int *fd, t_pipeline *cmd, t_list **envl)
{
	g_vars.pid = 0;
	// g_vars.pid = fork();
	if (g_vars.pid == 0)
	{
		if (in != 0)
		{
			dup2(in, STDIN_FILENO);
			close(in);
		}
		if (fd[1] != 1)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
		}
		if (fd[0] > 2)
			close(fd[0]);
		if (cmd->has_red)
			redirect(cmd);
		if (is_builtin(cmd->cmd[0]))
			exec_builtin(cmd->cmd, envl);
		else
		{
			execve(cmd->cmd[0], (char *const *)cmd->cmd, NULL);
			ft_putstr_fd(strerror(errno), STDERR_FILENO);
			write(2, "\n", 1);
			exit(errno);
		}
	}
}

int	is_builtin(char *cmd)
{
	if ((ft_strcmp("echo", cmd) == 0) || (ft_strcmp("env", cmd) == 0)
		|| (ft_strcmp("cd", cmd) == 0) || (ft_strcmp("export", cmd) == 0)
		|| (ft_strcmp("pwd", cmd) == 0) || (ft_strcmp("exit", cmd) == 0)
		|| (ft_strcmp("unset", cmd) == 0))
		return (1);
	else if ((ft_strcmp("ECHO", cmd) == 0) || (ft_strcmp("ENV", cmd) == 0)
		|| (ft_strcmp("CD", cmd) == 0) || (ft_strcmp("EXPORT", cmd) == 0)
		|| (ft_strcmp("PWD", cmd) == 0) || (ft_strcmp("EXIT", cmd) == 0)
		|| (ft_strcmp("UNSET", cmd) == 0))
		return (2);
	else
		return (0);
}

void	fork_pipes(t_pipeline *cmd, t_list **envl)
{
	int		in;
	int		fd[2];
	int		status;
	int		ret;

	in = 0;
	status = 0;
	ret = is_builtin(cmd->cmd[0]);
	while (cmd->next != NULL)
	{
		if (ret != 1)
		{
			cmd->cmd[0] = check_exec(cmd->cmd[0], *envl);
			if (cmd->cmd[0] == NULL)
				return ;
		}
		pipe(fd);
		spawn_proc(in, fd, cmd, envl);
		if (fd[1] > 2)
			close(fd[1]);
		if (in != 0)
			close(in);
		in = fd[0];
		cmd = cmd->next;
	}
	if (ret != 1)
	{
		cmd->cmd[0] = check_exec(cmd->cmd[0], *envl);
		if (cmd->cmd[0] == NULL)
			return ;
	}
	// g_vars.pid = fork();
	g_vars.pid = 0;
	if (g_vars.pid == 0)
	{
		if (in != 0)
		{
			dup2(in, STDIN_FILENO);
			close(in);
		}
		if (fd[1] > 2)
			close(fd[1]);
		if (cmd->has_red)
			redirect(cmd);
		if (is_builtin(cmd->cmd[0]))
			exec_builtin(cmd->cmd, envl);
		else
		{
			execve(cmd->cmd[0], (char *const *)cmd->cmd, NULL);
			ft_putstr_fd("msh: ", STDERR_FILENO);
			ft_putstr_fd(cmd->cmd[0], STDERR_FILENO);
			if (errno == ENOENT)
			{
				ft_putstr_fd(": command not found", STDERR_FILENO);
				g_vars.exit_code = 127;
			}
			else
				ft_putstr_fd(strerror(errno), STDERR_FILENO);
			write(2, "\n", 1);
			exit(errno);
		}
	}
	if (in != 0)
		close(in);
	while (waitpid(-1, &status, 0) > 0)
		if (WIFEXITED(status))
			g_vars.exit_code = WEXITSTATUS(status);
}
