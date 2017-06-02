/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 13:42:00 by svelhinh          #+#    #+#             */
/*   Updated: 2015/11/29 09:51:44 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dlen;
	size_t	tlen;

	dlen = ft_strlen(dst);
	tlen = dlen + ft_strlen(src);
	if (!(dst = (char *)ft_memchr(dst, '\0', size)))
		return (size + ft_strlen(src));
	while (*src && dlen < size - 1)
	{
		*dst++ = *src++;
		dlen++;
	}
	*dst = '\0';
	return (tlen);
}
