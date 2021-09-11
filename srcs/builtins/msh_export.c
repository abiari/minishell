/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 12:32:04 by abiari            #+#    #+#             */
/*   Updated: 2021/09/11 13:50:50 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fill_env(int print, char *new_value, char **tmp_str, t_envl **tmp_var)
{
	if (print)
	{
		(*tmp_var)->value = ft_strdup(new_value);
		*tmp_str = ft_strjoin((*tmp_var)->key, "=");
		(*tmp_var)->var = ft_strjoin(*tmp_str, (*tmp_var)->value);
	}
	else
	{
		(*tmp_var)->value = NULL;
		(*tmp_var)->var = ft_strdup((*tmp_var)->key);
	}
}

void	export_mod(char *var, char *new_value, int printable, t_list ***envl)
{
	t_list	*tmp;
	t_envl	*tmp_var;
	char	*tmp_str;

	tmp = **envl;
	tmp_str = NULL;
	while (tmp)
	{
		tmp_var = (t_envl *)tmp->content;
		if (ft_strcmp(var, tmp_var->key) == 0)
		{
			if (tmp_var->value)
				free(tmp_var->value);
			free(tmp_var->var);
			fill_env(printable, new_value, &tmp_str, &tmp_var);
			tmp_var->env_printable = printable;
			free(tmp_str);
			break ;
		}
		tmp = tmp->next;
	}
}

void	export_add(char *var, char *value, int printable, t_list ***envl)
{
	t_envl	*env;
	char	*tmp_str;

	tmp_str = NULL;
	env = malloc(sizeof(t_envl));
	if (env == NULL)
	{
		printf("msh: %s", strerror(errno));
		return ;
	}
	env->key = ft_strdup(var);
	if (printable)
	{
		env->value = ft_strdup(value);
		tmp_str = ft_strjoin(env->key, "=");
		env->var = ft_strjoin(tmp_str, env->value);
	}
	else
	{
		env->value = NULL;
		env->var = ft_strdup(env->key);
	}
	env->env_printable = printable;
	free(tmp_str);
	lst_append(*envl, env);
}

int	_export(char **args, t_list ***envl)
{
	int		i;
	int		printable;
	char	*key;
	char	*value;

	i = 0;
	while (args[i] != NULL)
	{
		is_printable(&printable, args[i]);
		key = find_env_key(args[i]);
		if (!check_key(key))
		{
			export_err(args[i]);
			return (1);
		}
		value = find_env_value(args[i]);
		if (find_env_var(key, *envl))
			export_mod(key, value, printable, envl);
		else
			export_add(key, value, printable, envl);
		free(key);
		i++;
	}
	return (0);
}

int	msh_export(char **args, t_list **envl)
{
	if (args[0] != NULL)
	{
		if (_export(args, &envl))
			return (1);
	}
	else
		print_env(envl);
	return (0);
}
