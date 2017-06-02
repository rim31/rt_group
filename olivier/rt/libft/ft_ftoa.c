/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 10:00:58 by svelhinh          #+#    #+#             */
/*   Updated: 2016/03/09 14:15:17 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <math.h>

static int		ft_nbrlen(int n)
{
	int i;

	i = 0;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char			*ft_ftoa(double n, int preci)
{
	char	*str;
	int		i;
	int		ipart;
	double	fpart;

	i = 0;
	ipart = (int)n;
	fpart = n - (double)ipart;
	str = ft_strdup(ft_itoa(ipart));
	str = ft_strjoin(str, ".");
	while (i < preci)
	{
		fpart = fpart * 10;
		i++;
	}
	i = 0;
	while (i < preci - ft_nbrlen(fpart))
	{
		str = ft_strjoin(str, "0");
		i++;
	}
	str = ft_strjoin(str, ft_itoa(fpart));
	return (str);
}
