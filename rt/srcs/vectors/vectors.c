/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 10:02:14 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/08 15:58:10 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vector	vecprod(const t_vector *v1, const t_vector *v2)
{
	t_vector	result;

	result.x = v1->y * v2->z - v1->z * v2->y;
	result.y = v1->z * v2->x - v1->x * v2->z;
	result.z = v1->x * v2->y - v1->y * v2->x;
	return (result);
}

t_vector	vecsub(const t_vector *v1, const t_vector *v2)
{
	t_vector result;

	result.x = v2->x - v1->x;
	result.y = v2->y - v1->y;
	result.z = v2->z - v1->z;
	return (result);
}

t_vector	vecadd(const t_vector *v1, const t_vector *v2)
{
	t_vector result;

	result.x = v2->x + v1->x;
	result.y = v2->y + v1->y;
	result.z = v2->z + v1->z;
	return (result);
}

void		vecscale(t_vector *v, const double factor)
{
	v->x *= factor;
	v->y *= factor;
	v->z *= factor;
}

double		vecdot(const t_vector *v1, const t_vector *v2)
{
	double	resx;
	double	resy;
	double	resz;
	double	result;

	resx = v1->x * v2->x;
	resy = v1->y * v2->y;
	resz = v1->z * v2->z;
	result = resx + resy + resz;
	return (result);
}
