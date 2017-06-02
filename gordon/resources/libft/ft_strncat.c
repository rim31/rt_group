/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grass-kw <grass-kw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 11:55:06 by grass-kw          #+#    #+#             */
/*   Updated: 2015/02/10 10:58:48 by grass-kw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	char	*tmp;
	int		i;

	tmp = s1;
	i = 0;
	while (tmp[i])
		i++;
	while (n--)
	{
		tmp[i] = *s2;
		i++;
		s2++;
	}
	tmp[i] = '\0';
	return (s1);
}
