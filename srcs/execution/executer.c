/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 11:43:08 by abiari            #+#    #+#             */
/*   Updated: 2021/06/01 14:59:02 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_double(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	*bin_path(char *cmd, t_list *envl)
{
	char	**split_path;
	char	*path;
	int		bin_fd;
	int		i;

	i = 0;
	split_path = ft_split((find_env_var("PATH", &envl))->value, ':');
	if (!split_path)
	{
		ft_putstr_fd("msh: No such file or directory\n", 2);
		return (NULL);
	}
	while (split_path[i])
	{
		split_path[i] = ft_strjoin(split_path[i], "/");
		path = ft_strjoin(split_path[i], cmd);
		bin_fd = open(path, O_RDONLY);
		if (bin_fd > 0)
		{
			path = ft_strdup(ft_strjoin(split_path[i], cmd));
			free_double(split_path);
			close(bin_fd);
			return (path);
		}
		i++;
	}
	ft_putstr_fd("msh: command not found\n", 2);
	free_double(split_path);
	return (NULL);
}

void	exec(t_pipeline *cmd, char **envp)
{
	// t_list	*envl;

	// envl = envp_to_envl(envp);
	if ((cmd->cmd[0] == NULL) && (cmd->has_red == 1))
		create_file(cmd);
	else
		fork_pipes(cmd, envp);
}
