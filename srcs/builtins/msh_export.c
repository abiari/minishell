/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 12:32:04 by abiari            #+#    #+#             */
/*   Updated: 2021/07/02 12:50:06 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	export_mod(char *var, char *new_value, int printable, t_list **envl)
{
	t_list	*tmp;
	t_envl	*tmp_var;
	char	*tmp_str;

	tmp = *envl;
	tmp_var = (t_envl *)(*envl);
	tmp_str = NULL;
	while (tmp)
	{
		tmp_var = (t_envl *)tmp->content;
		if (ft_strcmp(var, tmp_var->key) == 0)
		{
			if (tmp_var->value)
				free(tmp_var->value);
			free(tmp_var->var);
			if (printable)
			{
				tmp_var->value = ft_strdup(new_value);
				tmp_str = ft_strjoin(tmp_var->key, "=");
				tmp_var->var = ft_strjoin(tmp_str, tmp_var->value);
			}
			else
			{
				tmp_var->value = NULL;
				tmp_var->var = ft_strdup(tmp_var->key);
			}
			tmp_var->env_printable = printable;
			free(tmp_str);
			break ;
		}
		tmp = tmp->next;
	}
}

void	export_add(char *var, char *value, int printable, t_list **envl)
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
	lst_append(envl, env);
}

int	check_key(char *arg)
{
	int	i;

	i = 1;
	if (arg[0] != '_' && !ft_isalpha(arg[0]))
		return (0);
	while (arg[i])
	{
		if (!ft_isalpha(arg[i]) && !ft_isdigit(arg[i]) && arg[0] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	msh_export(char **args, t_list **envl)
{
	int		i;
	t_list	*tmp;
	int		printable;
	char	*key;
	char	*value;

	i = 0;
	if (args[0] != NULL)
	{
		while (args[i] != NULL)
		{
			if (ft_strchr(args[i], '=') != NULL)
				printable = 1;
			else
				printable = 0;
			key = find_env_key(args[i]);
			if (!check_key(key))
			{
				ft_putstr_fd("msh: export: `", 2);
				ft_putstr_fd(args[i], 2);
				ft_putendl_fd("': not a valid identifier", 2);
				return (1);
			}
			value = find_env_value(args[i]);
			if (find_env_var(key, envl))
				export_mod(key, value, printable, envl);
			else
				export_add(key, value, printable, envl);
			free(key);
			i++;
		}
	}
	else
	{
		tmp = *envl;
		while (tmp)
		{
			printf("declare -x %s\n", ((t_envl *)(tmp->content))->var);
			tmp = tmp->next;
		}
	}
	return (0);
}
