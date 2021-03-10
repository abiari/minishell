/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 16:08:37 by abiari            #+#    #+#             */
/*   Updated: 2021/03/10 10:54:11 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		msh_cd(char *path, t_list *envl)
{
	int		ret;
	char	*old_path;

	old_path = NULL;
	ret = 0;
	if ((old_path = getcwd(NULL, 0)) == NULL)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		return ((int)errno);
	}
	if ((ret = chdir(path)) != -1)
	{
		path = getcwd(NULL, 0);
		mod_env_var("PWD", path, &envl);
		if (find_env_var("OLDPWD", envl) != NULL)
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
