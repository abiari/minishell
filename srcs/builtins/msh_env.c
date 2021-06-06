/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 15:56:18 by abiari            #+#    #+#             */
/*   Updated: 2021/06/06 19:21:55 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	msh_env(char **args, t_list *envl)
{
	int		ret;
	t_envl	*tmp_cast;
	t_list	*tmp;

	if (args[0] != NULL)
	{
		ft_putstr_fd("bad usage\n", 2);
		return (1);
	}
	ret = 0;
	tmp = envl;
	while (tmp != NULL)
	{
		tmp_cast = ((t_envl *)(tmp)->content);
		if (tmp_cast->env_printable)
			printf("%s\n", tmp_cast->var);
		tmp = tmp->next;
	}
	return (ret);
}
