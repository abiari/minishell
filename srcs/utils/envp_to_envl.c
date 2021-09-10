/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_to_envl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 14:28:27 by abiari            #+#    #+#             */
/*   Updated: 2021/09/10 15:46:51 by abiari           ###   ########.fr       */
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
	int		i;
	t_list	*envl;
	t_envl	*env;

	i = 0;
	envl = NULL;
	while (envp[i] != NULL)
	{
		env = malloc(sizeof(t_envl));
		if (env == NULL)
		{
			printf("msh: %s", strerror(errno));
			exit(errno);
		}
		env->value = ft_strdup(find_env_value(envp[i]));
		env->var = ft_strdup(envp[i]);
		env->key = find_env_key(envp[i]);
		env->env_printable = 1;
		lst_append(&envl, env);
		i++;
	}
	return (envl);
}

char	**envl_to_envp(t_list **envl)
{
	t_list	*tmp;
	int		size;
	char	**envp;

	tmp = *envl;
	size = ft_lstsize(*envl);
	envp = (char **)malloc(size * sizeof(char *));
	if (!envp)
	{
		ft_putstr_fd(strerror(errno), 2);
		return (NULL);
	}
	size = 0;
	while (tmp)
	{
		envp[size] = ((t_envl *)(tmp->content))->var;
		size++;
		tmp = tmp->next;
	}
	return (envp);
}
