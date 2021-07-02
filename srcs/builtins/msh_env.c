/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 15:56:18 by abiari            #+#    #+#             */
/*   Updated: 2021/07/02 12:49:24 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	msh_env(char **args, t_list **envl)
{
	int		ret;
	t_envl	*tmp_cast;
	t_list	*tmp;

	if (args[0] != NULL)
	{
		ft_putstr_fd("msh: env: too many arguments\n", 2);
		return (1);
	}
	ret = 0;
	tmp = *envl;
	while (tmp != NULL)
	{
		tmp_cast = ((t_envl *)(tmp)->content);
		if (tmp_cast->env_printable)
		{
			write(1, tmp_cast->var, ft_strlen(tmp_cast->var));
			write(1, "\n", 1);
		}
		tmp = tmp->next;
	}
	return (ret);
}
