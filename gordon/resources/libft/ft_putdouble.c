/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdouble.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grass-kw <grass-kw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/25 17:39:28 by anonymous         #+#    #+#             */
/*   Updated: 2015/06/02 04:06:33 by grass-kw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "math.h"

void	ft_putdouble(double n, size_t afterpoint)
{
	int		ipart;
	double	fpart;

	ipart = (int)n;
	fpart = n - (double)ipart;
	if (fpart < 0)
		fpart *= -1.0;
	if (afterpoint != 0)
	{
		fpart = fpart * pow(10, afterpoint);
		ft_putnbr(ipart);
		ft_putchar('.');
		ft_putnbr(fpart);
	}
}
