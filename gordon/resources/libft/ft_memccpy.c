/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grass-kw <grass-kw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 13:39:00 by grass-kw          #+#    #+#             */
/*   Updated: 2015/02/10 11:01:55 by grass-kw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t len)
{
	char	*tmp_src;
	char	*tmp_dst;

	tmp_src = (char *)src;
	tmp_dst = (char *)dst;
	while (len--)
	{
		if (*tmp_src == c)
		{
			*tmp_dst = *tmp_src;
			tmp_dst++;
			return ((void *)tmp_dst);
		}
		*tmp_dst = *tmp_src;
		tmp_src++;
		tmp_dst++;
	}
	return (NULL);
}
