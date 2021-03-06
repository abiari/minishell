/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 14:28:27 by abiari            #+#    #+#             */
/*   Updated: 2021/03/06 16:07:55 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_env_key(const char *envp)
{
	int	len;

	len = 0;
	while (envp[len] != '=')
	{
		len++;
	}
	return (ft_substr(envp, 0, (size_t)len));
}

char	*find_env_value(const char *envp)
{
	char	*value;

	value = ft_strchr(envp, '=') + 1;

	return (value);
}

t_list	*envp_to_envl(char *envp[])
{
	int	i;
	t_list	*envl;
	t_list	*next_env;
	t_envl	*env;

	i = 0;
	envl = NULL;
	next_env = NULL;
	while (envp[i] != '\0')
	{
		env = (t_envl *)malloc(sizeof(env));
		env->key = find_env_key(envp[i]);
		env->value = find_env_value(envp[i]);
		env->var = ft_strdup(envp[i]);
		if (!envl)
			envl = ft_lstnew(env);
		else
		{
			next_env = ft_lstnew(env);
			ft_lstadd_back(&envl, next_env);
		}
		printf("%s=%s\n", env->key, env->value);
		i++;
	}
	return (envl);
}
