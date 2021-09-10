/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 17:35:24 by abiari            #+#    #+#             */
/*   Updated: 2021/09/10 11:15:24 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_proc(t_pipeline *cmd, t_list **envl)
{
	char	**envp;

	if (is_dir(cmd->cmd[0]))
	{
		ft_putstr_fd("msh: ", 2);
		ft_putstr_fd(cmd->cmd[0], 2);
		ft_putstr_fd(": is a directory\n", 2);
		exit(126);
	}
	envp = envl_to_envp(envl);
	execve(cmd->cmd[0], (char *const *)cmd->cmd, envp);
	ft_putstr_fd("msh: ", STDERR_FILENO);
	ft_putstr_fd(cmd->cmd[0], 2);
	if (errno == ENOENT && find_env_var("PATH", envl))
	{
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
	else
	{
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	}
	exit(errno);
}

void	spawn_proc(int in, int *fd, t_pipeline *cmd, t_list **envl)
{
	g_vars.pid = fork();
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
			exit(exec_builtin(cmd->cmd, envl));
		else
			exec_proc(cmd, envl);
	}
}

void	spawn_last(int in, int *fd, t_pipeline *cmd, t_list **envl)
{
	g_vars.pid = fork();
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
			exit(exec_builtin(cmd->cmd, envl));
		else
			exec_proc(cmd, envl);
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

void	fork_pipes(t_pipeline *cmd, t_list **envl)
{
	int		in;
	int		fd[2];

	in = 0;
	while (cmd->next != NULL)
	{
		if (check_if_builtin(cmd, envl))
			return ;
		pipe(fd);
		spawn_proc(in, fd, cmd, envl);
		if (fd[1] > 2)
			close(fd[1]);
		if (in != 0)
			close(in);
		in = fd[0];
		cmd = cmd->next;
	}
	if (check_if_builtin(cmd, envl))
		return ;
	spawn_last(in, fd, cmd, envl);
	if (in != 0)
		close(in);
	wait_exec();
}
