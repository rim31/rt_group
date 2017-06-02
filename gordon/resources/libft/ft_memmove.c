/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grass-kw <grass-kw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 13:45:41 by grass-kw          #+#    #+#             */
/*   Updated: 2015/02/10 10:49:16 by grass-kw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	unsigned char	tmp[n];
	int				i;

	i = -1;
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	while (++i < (int)n)
		*(tmp + i) = *(s + i);
	i = -1;
	while (++i < (int)n)
		*(d + i) = *(tmp + i);
	return (dst);
}
