/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grass-kw <grass-kw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 13:16:59 by grass-kw          #+#    #+#             */
/*   Updated: 2015/02/10 11:00:39 by grass-kw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	int		i;
	char	*tmp;

	tmp = (char *)b;
	i = 0;
	while (len--)
	{
		tmp[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
