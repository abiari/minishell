/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 16:08:37 by abiari            #+#    #+#             */
/*   Updated: 2021/03/07 19:39:17 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		msh_cd(char *path, t_list *envl)
{
	int 	ret;
	char	*old_path;

	old_path = NULL;
	ret = 0;
	if ((old_path = (t_envl *)find_env_var("PWD", envl)->value) == NULL)
	{
		printf("msh: PWD not found in env");
		return(1);
	}
	if ((ret = chdir(path) != -1))
	{
		mod_env_var("PWD", path, envl);
		add_env_var("OLD_PWD", old_path, envl);
	}
	else
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		free(old_path);
		return (errno);
	}
	return (ret);
}
