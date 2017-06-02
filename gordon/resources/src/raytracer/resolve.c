/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grass-kw <grass-kw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/20 15:38:24 by grass-kw          #+#    #+#             */
/*   Updated: 2016/04/21 06:53:46 by grass-kw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_v1.h"

double	resolve(double delta, double a, double b)
{
	double k;
	double k1;
	double k2;

	if (delta == ZERO)
	{
		k = (b * -1) / 2 * a;
		return (k);
	}
	if (delta > ZERO)
	{
		k1 = (b * -1) + sqrt(delta);
		k2 = (b * -1) - sqrt(delta);
		k = k1;
		k = (k2 > 0 && k2 < k1) ? k2 : k1;
		return (k);
	}
	return (ZERO);
}
