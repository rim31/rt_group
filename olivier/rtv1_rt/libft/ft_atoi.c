/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:32:13 by svelhinh          #+#    #+#             */
/*   Updated: 2016/02/18 14:52:06 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int i;
	int nbr;
	int negative;

	i = 0;
	nbr = 0;
	negative = 0;
	while (str[i] != '-' && str[i] != '+' && !(str[i] >= '0' && str[i] <= '9'))
	{
		if (str[i] > ' ' || ft_isascii(str[i]) == 0 || str[i] == '\0')
			return (0);
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
		i++;
	negative = (str[i - 1] == '-');
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		nbr = str[i++] - '0' + nbr * 10;
	if (negative == 1)
		nbr = 0 - nbr;
	return (nbr);
}
