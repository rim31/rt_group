/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grass-kw <grass-kw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 14:31:02 by grass-kw          #+#    #+#             */
/*   Updated: 2015/02/10 10:55:15 by grass-kw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ret;
	size_t	l;

	l = ft_strlen(s1);
	if (!(ret = (char *)malloc(sizeof(char) * (l + 1))))
		return (NULL);
	ft_memcpy((void *)ret, s1, l);
	ret[l] = '\0';
	return (ret);
}
