/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 11:12:44 by svelhinh          #+#    #+#             */
/*   Updated: 2015/12/04 09:03:28 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*tmp;

	i = 0;
	tmp = (char *)malloc(sizeof(char) * len);
	if (!tmp)
		return (NULL);
	ft_memcpy(tmp, src, len);
	while (i < len)
	{
		((char *)dst)[i] = tmp[i];
		i++;
	}
	return (dst);
}
