/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 09:50:44 by svelhinh          #+#    #+#             */
/*   Updated: 2015/12/05 13:11:34 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbword(char const *s, char c)
{
	int i;
	int countword;
	int firstletter;

	i = 0;
	countword = 0;
	firstletter = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && firstletter == 0)
		{
			countword++;
			firstletter++;
		}
		if (s[i] == c && firstletter > 0)
			firstletter = 0;
		i++;
	}
	return (countword);
}

static int	ft_wordlen(char const *word, char c, int *i)
{
	while (word[*i] == c && word[*i])
		(*i)++;
	return (*i);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tab_ptr;
	char	*str;
	int		start;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	str = (char*)s;
	tab_ptr = (char **)malloc(sizeof(*tab_ptr) * (ft_nbword(s, c) + 1));
	tab_ptr[ft_nbword(s, c)] = NULL;
	while (str[i] != '\0' && tab_ptr)
	{
		start = ft_wordlen(s, c, &i);
		while (str[i] != c && str[i] != '\0')
			i++;
		if (start == i)
			(tab_ptr[j] = NULL);
		else
			tab_ptr[j] = ft_strsub(str, start, i - start);
		j++;
	}
	return (tab_ptr);
}
