/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 16:08:37 by abiari            #+#    #+#             */
/*   Updated: 2021/03/09 18:13:14 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		msh_cd(char *path, t_list *envl)
{
	int 	ret;
	char	*old_path;

	old_path = NULL;
	ret = 0;
	if ((old_path = getcwd(NULL, 0)) == NULL)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		return((int)errno);
	}
	if ((ret = chdir(path)) != -1)
	{
		printf("old_pwd :%s\n", old_path);
		mod_env_var("PWD", path, &envl);
		if (find_env_var("OLD_PWD", envl) != NULL)
			add_env_var("OLD_PWD", old_path, &envl);
		else
			mod_env_var("OLD_PWD", path, &envl);
		t_list	*tmp = envl;
		while (envl->next)
		{
			tmp = envl->content;
			printf("|%s=%s|\n", ((t_envl *)tmp)->key, ((t_envl *)tmp)->value);
			envl = envl->next;
		}
		return 0;
		// printf("from msh_cd -> OLD_PWD: %s\n", ((t_envl *)find_env_var("OLD_PWD", envl))->var);
		// printf("from msh_cd -> OLD_PWD: %s\n", ((t_envl *)find_env_var("OLD_PWD", envl))->var);
	}
	else
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		free(old_path);
		return ((int)errno);
	}
	return (ret);
}
