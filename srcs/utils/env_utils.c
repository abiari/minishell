/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 19:33:40 by abiari            #+#    #+#             */
/*   Updated: 2021/09/10 10:48:28 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	mod_env_var(char *var, char *new_value, t_list **envl)
{
	t_list	*tmp;
	t_envl	*tmp_var;
	char	*tmp_str;

	tmp = *envl;
	tmp_var = (t_envl *)(*envl);
	while (tmp->next != NULL)
	{
		tmp_var = (t_envl *)tmp->content;
		if (ft_strcmp(var, tmp_var->key) == 0)
		{
			free(tmp_var->value);
			tmp_var->value = ft_strdup(new_value);
			tmp_str = ft_strjoin(tmp_var->key, "=");
			tmp_var->var = ft_strjoin(tmp_str, tmp_var->value);
			tmp_var->env_printable = 1;
			free(tmp_str);
			break ;
		}
		tmp = tmp->next;
	}
}

void	add_env_var(char *var, char *value, t_list **envl)
{
	t_envl	*env;
	char	*tmp_str;

	env = malloc(sizeof(t_envl));
	if (env == NULL)
	{
		printf("msh: %s", strerror(errno));
		return ;
	}
	env->key = ft_strdup(var);
	env->value = ft_strdup(value);
	tmp_str = ft_strjoin(env->key, "=");
	env->var = ft_strjoin(tmp_str, env->value);
	env->env_printable = 1;
	free(tmp_str);
	lst_append(envl, env);
}

t_envl	*find_env_var(char *var, t_list **envl)
{
	t_list	*tmp;

	tmp = *envl;
	while (tmp)
	{
		if (ft_strcmp(var, ((t_envl *)tmp->content)->key) == 0)
			return ((t_envl *)tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

void	envl_clear(void *content)
{
	free(((t_envl *)content)->key);
	free(((t_envl *)content)->value);
	free(((t_envl *)content)->var);
	free(content);
}
