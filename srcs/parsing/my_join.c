/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_join.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 16:33:45 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/09/18 16:33:55 by ael-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*my_strjoin(char *s1, char const *s2)
{
	char	*ret;

	if (!s1)
		return (NULL);
	ret = ft_strjoin(s1, s2);
	free(s1);
	return (ret);
}

char	*to_join(char **spaces)
{
	int		i;
	char	*cmd;

	i = 0;
	cmd = ft_strdup("");
	while (spaces[++i])
	{
		cmd = my_strjoin(cmd, spaces[i]);
		cmd = my_strjoin(cmd, " ");
	}
	return (cmd);
}
