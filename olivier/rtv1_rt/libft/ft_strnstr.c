/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 16:53:36 by svelhinh          #+#    #+#             */
/*   Updated: 2015/12/02 11:48:51 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_intinit(size_t *i, int *i3)
{
	*i = 0;
	*i3 = 0;
}

char		*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		i2;
	int		i3;
	char	*s3;

	ft_intinit(&i, &i3);
	s3 = (char *)malloc(sizeof(char) * ft_strlen(s2) + 1);
	if (ft_strcmp(s2, "") == 0)
		return ((char *)s1);
	while (s1[i = i3] != '\0' && i < n)
	{
		i2 = 0;
		while (s2[i2++] == s1[i++])
		{
			if (s2[i2] == '\0')
			{
				s3 = &((char *)s1)[i3];
				return (s3);
			}
			if (i == n)
				return (NULL);
		}
		i3++;
	}
	return (NULL);
}
