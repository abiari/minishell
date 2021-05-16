/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 11:43:08 by abiari            #+#    #+#             */
/*   Updated: 2021/05/15 09:15:05 by abiari           ###   ########.fr       */
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
	int		i = 0;

	split_path = ft_split((find_env_var("PATH", &envl))->value, ':');
	if (!split_path)
	{
		// ft_putstr_fd("msh: $PATH variable corrupted", 2);
		return(NULL);
	}
	while (split_path[i])
	{
		split_path[i] = ft_strjoin(split_path[i], "/");
		path = ft_strjoin(split_path[i], cmd);
		printf("%s\n", path);
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
	free_double(split_path);
	return(NULL);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*exec_path;
	t_list	*envl;

	(void)argc;
	(void)argv;
	envl = envp_to_envl(envp);
	// while (envl->next)
	// {
	// 	printf("%s\n", ((t_envl *)envl->content)->var);
	// 	envl = envl->next;
	// }
	exec_path = bin_path("ls", envl);
	if (exec_path)
		printf("bin exists at: %s", exec_path);
	else
		printf("command not found");
	return(0);
}
