/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 19:33:40 by abiari            #+#    #+#             */
/*   Updated: 2021/03/07 20:26:42 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	mod_env_var(char *var, char *new_value, t_list *envl)
{
	t_list	*tmp;

	tmp = envl;
	while (tmp->next)
	{
		if (strcmp(var, ((t_envl *)tmp)->key) != NULL)
		{
			free(((t_envl *)tmp)->value);
			((t_envl *)tmp)->value = ft_strdup(new_value);
			break;
		}
	}
}

void	add_env_var(char *var, char *value, t_list *envl)
{
	t_envl	*env;

	if ((env = malloc(sizeof(t_envl))) == NULL)
	{
		printf("msh: %s", strerror(errno));
		return(errno);
	}
	env->key = var;
	env->value = value;
	env->var = ft_strjoin(env->key, env->value);
	lst_append(&envl, env);
}

t_envl	*find_env_var(char *var, t_list *envl)
{
	t_list	*tmp;

	tmp = envl;
	while (tmp->next)
	{
		if(strcmp(var, ((t_envl *)tmp)->key) != NULL)
			return((t_envl *)tmp);
		tmp = tmp->next;
	}
	return(NULL);
}

void	delete_env_var(char *var, t_list *envl)
{
	t_list	*tmp;

	tmp = envl;
	while (envl != NULL)
	{
		if(ft_strcmp(((t_envl *)envl->next)->key,var) != NULL)
			
	}

}
