/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_spc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/17 22:13:31 by anonymous         #+#    #+#             */
/*   Updated: 2015/05/12 14:35:22 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim_spc(char const *s)
{
	int i;
	int j;

	if (!s)
		return (NULL);
	i = 0;
	j = ft_strlen(s);
	if (!s)
		return (NULL);
	while (ft_ispace(*(s + i)))
		i++;
	while (ft_ispace(*(s + j - 1)))
		j--;
	return (ft_strsub(s, i, (j != 0) ? j -= i : j));
}
