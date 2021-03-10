/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 16:15:43 by abiari            #+#    #+#             */
/*   Updated: 2021/03/10 10:54:28 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		msh_pwd(t_list *envl)
{
	int		ret;
	char	*cwd;

	ret = 0;
	if ((cwd = getcwd(NULL, 0)) == NULL)
	{
		ft_putstr_fd(strerror(errno), 2);
		return (errno);
	}
	ft_putstr_fd(cwd, 1);
	return (ret);
}
