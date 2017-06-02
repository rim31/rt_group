/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grass-kw <grass-kw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 14:46:23 by grass-kw          #+#    #+#             */
/*   Updated: 2015/02/10 10:59:13 by grass-kw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dst, const char *src)
{
	size_t	l;
	char	*tmp;

	tmp = dst;
	l = ft_strlen(src);
	while ((l-- + 1))
		*tmp++ = *src++;
	return (dst);
}
