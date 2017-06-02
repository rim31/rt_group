/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grass-kw <grass-kw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/26 11:31:33 by grass-kw          #+#    #+#             */
/*   Updated: 2015/02/10 10:44:40 by grass-kw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_len(int n)
{
	int		res;

	res = 1;
	while (n < -9 || n > 9)
	{
		res++;
		n = n / 10;
	}
	if (n >= 0)
		return (res);
	else
		return (res + 1);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		i;
	int		nvalue;

	nvalue = n;
	i = ft_len(n);
	res = (char *)ft_memalloc(sizeof(char) * i + 1);
	while (i--)
	{
		if (n < 0)
			res[i] = (((n % 10) * -1) + 48);
		else
			res[i] = ((n % 10) + 48);
		n = n / 10;
	}
	if (nvalue < 0)
		res[0] = '-';
	return (res);
}
