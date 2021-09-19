/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 17:35:24 by abiari            #+#    #+#             */
/*   Updated: 2021/09/19 11:23:52 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_proc(t_pipeline *cmd, t_list **envl)
{
	char	**envp;

	exit_if_dir(cmd);
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
		if (errno == EACCES)
			exit(126);
	}
	if (!find_env_var("PATH", envl))
		exit(127);
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

void	last_pipe_node(t_pipeline *cmd, int in, int *fd, t_list **envl)
{
	if (cmd->cmd[0] != NULL)
	{
		spawn_last(in, fd, cmd, envl);
		if (in != 0)
			close(in);
	}
	else
		create_file(cmd);
}

void	fork_pipes(t_pipeline *cmd, t_list **envl)
{
	int		in;
	int		fd[2];

	in = 0;
	while (cmd->next != NULL)
	{
		if (files_in_pipe(&cmd, &in, fd))
			continue ;
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
	last_pipe_node(cmd, in, fd, envl);
	wait_exec();
}
