/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 16:15:43 by abiari            #+#    #+#             */
/*   Updated: 2021/07/02 08:45:28 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	msh_pwd(char **args, t_list *envl)
{
	char	*cwd;
	t_envl	*pwd;

	(void)args;
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		/* check pwd env var in this case and don't return */
		pwd = find_env_var("PWD", &envl);
		ft_putstr_fd(pwd->value, 1);
		// ft_putendl_fd(strerror(errno), 2);
		// return (errno);
	}
	ft_putendl_fd(cwd, 1);
	return (0);
}
