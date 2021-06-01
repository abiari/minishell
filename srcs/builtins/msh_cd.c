/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 16:08:37 by abiari            #+#    #+#             */
/*   Updated: 2021/05/31 10:17:37 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	msh_cd(char *path, t_list *envl)
{
	int		ret;
	char	*old_path;

	old_path = NULL;
	ret = 0;
	old_path = getcwd(NULL, 0);
	if (old_path == NULL)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		return ((int)errno);
	}
	ret = chdir(path);
	if (ret != -1)
	{
		path = getcwd(NULL, 0);
		mod_env_var("PWD", path, &envl);
		if (find_env_var("OLDPWD", &envl) != NULL)
			add_env_var("OLDPWD", old_path, &envl);
		else
			mod_env_var("OLDPWD", old_path, &envl);
	}
	else
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		free(old_path);
		return ((int)errno);
	}
	return (ret);
}
