/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 10:48:30 by abiari            #+#    #+#             */
/*   Updated: 2021/09/10 10:48:48 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_lstdelone2(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (*lst && del)
	{
		tmp = *lst;
		del((*lst)->content);
		*lst = (*lst)->next;
		free(tmp);
	}
}

int	delete_env_var(char *var, t_list **envl)
{
	t_list	*tmp;
	t_list	*prev;

	tmp = *envl;
	if (tmp != NULL && (ft_strcmp(((t_envl *)tmp->content)->key, var) == 0))
	{
		ft_lstdelone2(envl, envl_clear);
		return (0);
	}
	while (tmp->next != NULL)
	{
		prev = tmp;
		tmp = tmp->next;
		if (ft_strcmp(((t_envl *)tmp->content)->key, var) == 0)
		{
			prev->next = tmp->next;
			envl_clear(tmp->content);
			free(tmp);
			return (0);
		}
	}
	return (1);
}
