/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 16:15:43 by abiari            #+#    #+#             */
/*   Updated: 2021/06/07 18:08:21 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	msh_pwd(char **args, t_list *envl)
{
	char	*cwd;

	(void)args;
	(void)envl;
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		ft_putstr_fd(strerror(errno), 2);
		return (errno);
	}
	ft_putstr_fd(cwd, 1);
	ft_putstr_fd("\n", 1);
	return (0);
}
