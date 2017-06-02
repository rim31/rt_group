/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 16:08:30 by svelhinh          #+#    #+#             */
/*   Updated: 2016/03/11 12:21:36 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	size_t	length_s1;
	size_t	length_s2;
	size_t	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if (s2[0] == '\0')
		return ((char *)s1);
	length_s1 = ft_strlen(s1);
	length_s2 = ft_strlen(s2);
	if (length_s1 < length_s2)
		return (NULL);
	while (i <= length_s1 - length_s2)
	{
		if (ft_memcmp(&s1[i], &s2[0], length_s2) == 0)
			return ((char *)&s1[i]);
		i++;
	}
	return (NULL);
}
