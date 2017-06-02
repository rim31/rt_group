/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 10:00:58 by svelhinh          #+#    #+#             */
/*   Updated: 2016/02/09 17:16:32 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

static char		ft_negative(int *n, char c)
{
	c = '-';
	(*n == -2147483648) ? (*n = 2147483647) : (*n *= -1);
	return (c);
}

char			*ft_itoa(int n)
{
	char	*str;
	int		i;
	int		isave;
	int		nsave;

	i = ft_nbrlen(n);
	isave = i;
	if (!(str = (char *)malloc(sizeof(char) * i)))
		return (NULL);
	nsave = n;
	(n == 0) ? (str[0] = '0') : (0);
	(n < 0) ? (str[0] = ft_negative(&n, str[0])) : (i--);
	while (n != 0)
	{
		str[i] = '0' + n % 10;
		n /= 10;
		i--;
	}
	if (nsave <= 0)
		str[isave + 1] = '\0';
	else
		str[isave] = '\0';
	(nsave == -2147483648) ? (str[isave] += 1) : (0);
	return (str);
}
