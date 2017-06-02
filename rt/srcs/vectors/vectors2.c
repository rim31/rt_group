/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grass-kw <grass-kw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 03:25:59 by grass-kw          #+#    #+#             */
/*   Updated: 2016/06/11 14:56:29 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		normalize(t_vector *v1)
{
	double		vdist;

	vdist = sqrt(vecdot(v1, v1));
	v1->x /= vdist;
	v1->y /= vdist;
	v1->z /= vdist;
}

t_vector	new_vector(const double x, const double y, const double z)
{
	t_vector	new_vector;

	new_vector.x = x;
	new_vector.y = y;
	new_vector.z = z;
	return (new_vector);
}

t_color		new_color(const double r, const double g, const double b)
{
	t_color	new_color;

	new_color.r = r;
	new_color.g = g;
	new_color.b = b;
	return (new_color);
}
