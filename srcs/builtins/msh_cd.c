/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 16:08:37 by abiari            #+#    #+#             */
/*   Updated: 2021/07/02 12:51:33 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	msh_cd(char **args, t_list **envl)
{
	int		ret;
	char	*old_path;
	char	*path;
	char	*home;
	t_envl	*env_var;

	path = args[0];
	if (path != NULL)
		if (path[0] == '\0')
			return (0);
	old_path = NULL;
	ret = 0;
	old_path = getcwd(NULL, 0);
	home = NULL;
	if (old_path == NULL)
	{
		if (errno == ENOENT)
		{
			env_var = find_env_var("PWD", envl);
			old_path = ft_strdup(env_var->value);
		}
		else
		{
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
			return (1);
		}
	}
	if (path == NULL || (ft_strcmp(path, "~") == 0))
	{
		env_var = find_env_var("HOME", envl);
		if (!env_var)
		{
			ft_putendl_fd("msh : cd: HOME not set", 2);
			free(old_path);
			return (1);
		}
		else
		{
			home = env_var->value;
		}
		if (home != NULL)
			ret = chdir(home);
		else
		{
			ft_putendl_fd("msh: cd: HOME not set", 2);
			g_vars.exit_code = 1;
			return (g_vars.exit_code);
		}
	}
	else
	{
		if (!ft_strcmp(path, "."))
		{
			env_var = find_env_var("PWD", envl);
			ret = chdir(env_var->value);
		}
		else
			ret = chdir(path);
	}
	if (ret != -1)
	{
		path = getcwd(NULL, 0);
		mod_env_var("PWD", path, envl);
		if (!getenv("OLDPWD"))
			add_env_var("OLDPWD", old_path, envl);
		else
			mod_env_var("OLDPWD", old_path, envl);
	}
	else
	{
		if (errno == ENOENT && !ft_strcmp(path, "."))
		{
			env_var = find_env_var("PWD", envl);
			ft_putendl_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory", 2);
			mod_env_var("PWD", ft_strjoin(env_var->value, "/."), envl);
			env_var = find_env_var("OLDPWD", envl);
			if (!env_var)
				add_env_var("OLDPWD", old_path, envl);
			else
				mod_env_var("OLDPWD", old_path, envl);
		}
		else
		{
			ft_putstr_fd("msh: ", 2);
			ft_putstr_fd(path, 2);
			ft_putstr_fd(" :", 2);
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
			free(old_path);
			return (1);
		}
	}
	g_vars.exit_code = 0;
	return (ret);
}
