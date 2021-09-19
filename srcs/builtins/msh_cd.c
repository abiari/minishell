/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 16:08:37 by abiari            #+#    #+#             */
/*   Updated: 2021/09/19 08:42:40 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	mod_wd(char **path, char *old_path, t_list ***envl)
{
	*path = getcwd(NULL, 0);
	mod_env_var("PWD", *path, *envl);
	if (!getenv("OLDPWD"))
		add_env_var("OLDPWD", old_path, *envl);
	else
		mod_env_var("OLDPWD", old_path, *envl);
}

int	set_old_path(char **old_path, t_list **envl)
{
	*old_path = getcwd(NULL, 0);
	if (*old_path == NULL)
	{
		if (errno == ENOENT)
			*old_path = ft_strdup(find_env_var("PWD", envl)->value);
		else
		{
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
			return (1);
		}
	}
	return (0);
}

void	chdir_to_path(int *ret, char *path, t_list **envl)
{
	if (!ft_strcmp(path, "."))
		*ret = chdir(find_env_var("PWD", envl)->value);
	else
		*ret = chdir(path);
}

int	msh_cd(char **args, t_list **envl)
{
	int		ret;
	char	*old_path;
	char	*path;

	path = args[0];
	if (path != NULL)
		if (path[0] == '\0')
			return (0);
	old_path = NULL;
	ret = 0;
	if (set_old_path(&old_path, envl))
		return (1);
	if (path == NULL || (ft_strcmp(path, "~") == 0))
	{
		if (cd_home(&old_path, &ret, envl))
			return (1);
	}
	else
		chdir_to_path(&ret, path, envl);
	if (ret != -1)
		mod_wd(&path, old_path, &envl);
	else
		if (cd_err(path, &old_path, &envl))
			return (1);
	return (ret);
}
