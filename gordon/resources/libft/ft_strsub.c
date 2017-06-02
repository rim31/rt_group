/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grass-kw <grass-kw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/26 11:29:12 by grass-kw          #+#    #+#             */
/*   Updated: 2015/04/09 14:38:27 by grass-kw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	if (!(ret = ft_strnew(len)))
		return (NULL);
	while (start--)
		s++;
	while (len--)
	{
		ret[i] = *s;
		i++;
		s++;
	}
	return (ret);
}
