/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 12:32:04 by abiari            #+#    #+#             */
/*   Updated: 2021/06/24 09:01:39 by abiari           ###   ########.fr       */
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
	while (tmp)
	{
		tmp_var = (t_envl *)tmp->content;
		if (ft_strcmp(var, tmp_var->key) == 0)
		{
			free(tmp_var->value);
			tmp_var->value = ft_strdup(new_value);
			tmp_str = ft_strjoin(tmp_var->key, "=");
			tmp_var->var = ft_strjoin(tmp_str, tmp_var->value);
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
	env->env_printable = printable;
	free(tmp_str);
	lst_append(envl, env);
}

int	msh_export(char **args, t_list *envl)
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
			value = find_env_value(args[i]);
			if (find_env_var(key, &envl))
				export_mod(key, value, printable, &envl);
			else
				export_add(key, value, printable, &envl);
			free(key);
			i++;
		}
	}
	else
	{
		tmp = envl;
		while (tmp)
		{
			printf("declare -x %s\n", ((t_envl *)(tmp->content))->var);
			tmp = tmp->next;
		}
	}
	return (0);
}
