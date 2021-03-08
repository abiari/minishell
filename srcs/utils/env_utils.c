/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 14:28:27 by abiari            #+#    #+#             */
/*   Updated: 2021/03/08 14:44:09 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_env_key(const char *envp)
{
	int	len;

	len = 0;
	while (envp[len] && envp[len] != '=')
	{
		len++;
	}
	// char *hell = ft_substr(envp, 0, len);
	return (ft_substr(envp, 0, len));
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
	while (envp[i] != NULL)
	{
		if ((env = malloc(sizeof(t_envl))) == NULL)
		{
			printf("msh: %s", strerror(errno));
			exit(errno);
		}
		env->value = find_env_value(envp[i]);
		env->var = ft_strdup(envp[i]);
		env->key = find_env_key(envp[i]);
		if (!envl)
			envl = ft_lstnew(env);
		else
			lst_append(&envl, env);
		i++;
	}
	return (envl);
}
