/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_spc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/17 22:51:40 by anonymous         #+#    #+#             */
/*   Updated: 2015/05/12 14:37:03 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(char *s)
{
	int	i;
	int	j;
	int	w;

	w = 0;
	i = 0;
	while (*(s + i) != '\0')
	{
		while (ft_ispace(*(s + i)))
			i++;
		j = i;
		while (*(s + i) != '\0' && !ft_ispace(*(s + i)))
			i++;
		if (i != j)
			w++;
	}
	return (w + 1);
}

char		**ft_strsplit_spc(char const *s)
{
	char	**tab;
	int		ij[2];
	int		w;

	if (!s)
		return (NULL);
	if (!(tab = (char **)ft_memalloc(sizeof(char *) * ft_count((char *)s))))
		return (NULL);
	w = 0;
	ij[0] = 0;
	while (*(s + ij[0]) != '\0' && !(ij[1] = 0))
	{
		while (ft_ispace(*(s + ij[0])) && (ij[1] = ij[0] + 1))
			ij[0]++;
		while (*(s + ij[0]) != '\0' && !ft_ispace(*(s + ij[0])))
			ij[0]++;
		if (ij[0] == ij[1])
			return (tab);
		tab[w++] = ft_strndup(s + ij[1], ij[0] - ij[1]);
	}
	tab[w] = 0;
	return (tab);
}
