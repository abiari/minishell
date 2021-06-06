/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 11:43:08 by abiari            #+#    #+#             */
/*   Updated: 2021/06/06 19:17:24 by abiari           ###   ########.fr       */
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

void	exec_builtin(char **cmd, char **envp)
{
	static char	*builtin_str[7] = {
	"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	static	int	(*builtin_func[7])(char **, t_list *) = {
	&msh_echo, &msh_cd, &msh_pwd, &msh_export,
	&msh_unset, &msh_env, &msh_exit};
	int			j;

	j = 0;
	while (j < 7)
	{
		if (strcmp(cmd[0], builtin_str[j]) == 0)
			(g_vars.exit_code = (
						*builtin_func[j])(&cmd[1], envp_to_envl(envp)));
		j++;
	}
}

void	exec(t_pipeline *cmd, char **envp)
{
	if ((cmd->cmd[0] == NULL) && (cmd->has_red == 1))
		create_file(cmd);
	else if ((cmd->next == NULL) && is_builtin(cmd->cmd[0])
		&& cmd->has_red == 0)
		exec_builtin(cmd->cmd, envp);
	else
		fork_pipes(cmd, envp);
}
