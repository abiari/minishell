/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 18:10:58 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/05/25 13:02:53 by ael-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	two_d_counter(char **two_d)
{
	int i;

	i = 0;
	if (!two_d)
		return (-1);
	while (two_d[i])
		i++;
	return (i);
}

int	space_counter(int *comma)
{
	int	i;

	i = 0;
	while (comma[i] != -2)
		i++;
	return (i);
}
