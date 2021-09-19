/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 20:40:42 by abiari            #+#    #+#             */
/*   Updated: 2021/09/19 11:53:29 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_wlen(char const *str, int i, int *nbword, int c)
{
	*nbword += 1;
	while (str[i] != c && str[i] != '\0')
		i++;
	return (i);
}

void	ft_free_it(char **tab, int n)
{
	int	i;

	i = 0;
	while (i > n)
		free(tab[i++]);
	free(tab);
	tab = NULL;
}

int	ft_fill(char **tab, char const *str, int *nbword, int c)
{
	int		wlen;
	int		j;
	char	*tmp;
	int		sv;

	ft_reset(&wlen, &sv);
	while (str[wlen] != c && str[wlen] != '\0')
		wlen++;
	tmp = (char *)malloc((wlen + 1) * sizeof(char));
	if (!tmp)
	{
		ft_free_it(tab, *nbword);
		*nbword = 0;
		return (ft_strlen(str));
	}
	tmp[wlen] = '\0';
	j = 0;
	while (sv < wlen)
	{
		tmp[j] = str[sv++];
		j++;
	}
	tab[*nbword] = tmp;
	*nbword += 1;
	return (wlen);
}

void	alloc_tab(char ***tab, int *i, int *nb_wrds)
{
	*tab = (char **)malloc((*nb_wrds + 1) * sizeof(char *));
	(*tab)[*nb_wrds] = 0;
	*i = 0;
	*nb_wrds = 0;
}

char	**ft_split(char const *str, char c)
{
	int		i;
	char	**tab;
	int		number_words;

	ft_reset(&i, &number_words);
	if (!str)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] != c)
			i = ft_wlen(str, i, &number_words, c);
		else
			i++;
	}
	alloc_tab(&tab, &i, &number_words);
	while (str[i] != '\0')
	{
		if (str[i] != c)
			i += ft_fill(tab, str + i, &number_words, c);
		else
			i++;
	}
	if (!number_words && !tab)
		return (NULL);
	return (tab);
}
