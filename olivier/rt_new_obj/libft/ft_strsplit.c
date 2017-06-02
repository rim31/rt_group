/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grass-kw <grass-kw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/09 15:25:44 by grass-kw          #+#    #+#             */
/*   Updated: 2015/04/09 16:25:31 by grass-kw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(char *s, char c)
{
	int	i;
	int	j;
	int	w;

	w = 0;
	i = 0;
	while (*(s + i) != '\0')
	{
		while (*(s + i) == c)
			i++;
		j = i;
		while (*(s + i) != '\0' && *(s + i) != c)
			i++;
		if (i != j)
			w++;
	}
	return (w + 1);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		ij[2];
	int		w;

	if (!s)
		return (NULL);
	if (!(tab = (char **)ft_memalloc(sizeof(char *) * ft_count((char *)s, c))))
		return (NULL);
	w = 0;
	ij[0] = 0;
	while (*(s + ij[0]) != '\0' && !(ij[1] = 0))
	{
		while (*(s + ij[0]) == c && (ij[1] = ij[0] + 1))
			ij[0]++;
		while (*(s + ij[0]) != '\0' && *(s + ij[0]) != c)
			ij[0]++;
		if (ij[0] == ij[1])
			return (tab);
		tab[w++] = ft_strndup(s + ij[1], ij[0] - ij[1]);
	}
	tab[w] = 0;
	return (tab);
}
