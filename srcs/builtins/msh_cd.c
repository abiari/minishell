/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 16:08:37 by abiari            #+#    #+#             */
/*   Updated: 2021/09/12 16:00:13 by abiari           ###   ########.fr       */
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

int	cd_home(char **old_path, int *ret, t_list **envl)
{
	t_envl	*env_var;
	char	*home;

	home = NULL;
	env_var = find_env_var("HOME", envl);
	if (!env_var)
	{
		ft_putendl_fd("msh : cd: HOME not set", 2);
		free(*old_path);
		g_vars.exit_code = 1;
		return (1);
	}
	else
		home = env_var->value;
	if (home != NULL)
		*ret = chdir(home);
	else
	{
		ft_putendl_fd("msh: cd: HOME not set", 2);
		g_vars.exit_code = 1;
		return (g_vars.exit_code);
	}
	return (0);
}

int	msh_cd(char **args, t_list **envl)
{
	int		ret;
	char	*old_path;
	char	*path;
	t_envl	*env_var;

	path = args[0];
	if (path != NULL)
		if (path[0] == '\0')
			return (0);
	old_path = NULL;
	ret = 0;
	old_path = getcwd(NULL, 0);
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
		if (cd_home(&old_path, &ret, envl))
			return (1);
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
		if (cd_err(path, &old_path, &envl))
			return (1);
	return (ret);
}
