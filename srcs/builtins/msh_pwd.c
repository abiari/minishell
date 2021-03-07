/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 16:15:43 by abiari            #+#    #+#             */
/*   Updated: 2021/03/07 19:38:20 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		msh_pwd(t_list *envl)
{
	int		ret;
	t_envl	*pwd_var;

	ret = 0;
	if ((pwd_var = find_env_var("PWD", envl)) == NULL)
	{
		ft_putstr_fd("PWD env variable not set", 2);
		return (1);
	}
	ft_putstr_fd(pwd_var->value, 1);
	free(pwd_var);
	return(ret);
}
