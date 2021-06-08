/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 12:32:04 by abiari            #+#    #+#             */
/*   Updated: 2021/06/07 18:06:04 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	msh_export(char **args, t_list *envl)
{
	int		i;
	t_envl	*env_var;
	t_list	*tmp;

	i = 0;
	if (args[0] != NULL)
	{
		while (args[i] != NULL)
		{
			if (ft_strchr(args[i], '=') != NULL)
			{
				env_var = malloc(sizeof(t_envl));
				env_var->key = find_env_key(args[i]);
				env_var->value = ft_strdup(find_env_value(args[i]));
				env_var->var = ft_strdup(args[i]);
				env_var->env_printable = 1;
				lst_append(&envl, env_var);
			}
			else
			{
				env_var = malloc(sizeof(t_envl));
				env_var->key = ft_strdup(args[i]);
				env_var->value = NULL;
				env_var->var = ft_strdup(args[i]);
				env_var->env_printable = 0;
			}
			i++;
		}
	}
	else
	{
		tmp = envl;
		while ((tmp)->next)
		{
			printf("declare -x %s\n", ((t_envl *)(tmp->content))->var);
			(tmp) = (tmp)->next;
		}
	}
	return (0);
}
