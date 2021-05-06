/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 16:15:43 by abiari            #+#    #+#             */
/*   Updated: 2021/05/06 11:37:39 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		msh_pwd(t_list *envl)
{
	char	*cwd;

	if ((cwd = getcwd(NULL, 0)) == NULL)
	{
		ft_putstr_fd(strerror(errno), 2);
		return (errno);
	}
	ft_putstr_fd(cwd, 1);
	return (0);
}
