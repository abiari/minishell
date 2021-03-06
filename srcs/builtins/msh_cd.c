/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gru <gru@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 16:08:37 by abiari            #+#    #+#             */
/*   Updated: 2021/03/05 20:10:16 by gru              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_env_var(char *var, char *envp[])
{
	int		i;
	int		j;
	char	*match;

	i = 0;
	j = 0;
	match = NULL;
	while (envp[i])
	{
		if ((match = ft_strstr(envp[i], var)) != NULL)
			break;
		i++;
	}
	return (match);
}

int		msh_cd(char *path, char *envp[])
{
	int 	ret;
	char	*pwd_var;

	ret = 0;	
	if ((ret = chdir(path) != -1))
	{
		pwd_var = find_env_var("PWD", envp);
	}
	else
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
	return (ret);
}