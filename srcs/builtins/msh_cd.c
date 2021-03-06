/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 16:08:37 by abiari            #+#    #+#             */
/*   Updated: 2021/03/06 18:55:21 by abiari           ###   ########.fr       */
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

int		msh_cd(char *path, t_list *envl)
{
	int 	ret;
	char	*old_path;

	old_path = NULL;
	ret = 0;
	if ((old_path = (t_envl *)find_env_var("PWD", envl)->value) == NULL)
	{
		printf("msh: PWD not found in env");
		return(1);
	}
	if ((ret = chdir(path) != -1))
	{
		mod_env_var("PWD", path, envl);
		add_env_var("OLD_PWD", old_path, envl);
	}
	else
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		return (errno);
	}
	return (ret);
}
