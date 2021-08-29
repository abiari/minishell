/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rand_gen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 13:08:56 by abiari            #+#    #+#             */
/*   Updated: 2021/08/28 15:04:31 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*rand_str(void)
{
	int		file;
	char	*str;

	file = open("/dev/random", O_RDONLY);
	str = (char *)malloc(10);
	read(file, str, 10);
	close(file);
	return (str);
}
