/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 08:42:55 by abiari            #+#    #+#             */
/*   Updated: 2021/09/19 08:43:13 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cd_err(char *path, char **old_path, t_list ***envl)
{
	t_envl	*env_var;

	if (errno == ENOENT && !ft_strcmp(path, "."))
	{
		env_var = find_env_var("PWD", *envl);
		ft_putstr_fd("cd: error retrieving current directory: getcwd: ", 2);
		ft_putstr_fd("cannot access parent directories", 2);
		ft_putendl_fd(": No such file or directory", 2);
		mod_env_var("PWD", ft_strjoin(env_var->value, "/."), *envl);
		env_var = find_env_var("OLDPWD", *envl);
		if (!env_var)
			add_env_var("OLDPWD", *old_path, *envl);
		else
			mod_env_var("OLDPWD", *old_path, *envl);
	}
	else
	{
		ft_putstr_fd("msh: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(" :", 2);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		free(*old_path);
		return (1);
	}
	return (0);
}
