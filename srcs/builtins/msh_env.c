/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 15:56:18 by abiari            #+#    #+#             */
/*   Updated: 2021/03/12 12:30:03 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		msh_env(t_list **envl)
{
	int		ret;
	t_envl	*tmp_cast;
	t_list	*tmp;

	ret = 0;

	tmp = *envl;
	while (tmp != NULL)
	{
		tmp_cast = ((t_envl *)(tmp)->content);
		printf("%s\n", tmp_cast->var);
		tmp = tmp->next;
	}
	return (ret);
}
