/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 12:32:04 by abiari            #+#    #+#             */
/*   Updated: 2021/03/12 18:28:27 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		msh_export(char **args, t_list **envl)
{
	int		i;
	t_envl	*env_var;

	i = 0;
	while (args[i] != NULL)
	{
		if (ft_strchr(args[i], '=') != NULL)
		{
			env_var = malloc(sizeof(t_envl));
			env_var->key = find_env_key(args[i]);
			env_var->value = ft_strdup(find_env_value(args[i]));
			env_var->var = ft_strdup(args[i]);
			lst_append(envl, env_var);
		}
		i++;
	}
	return (0);
}
