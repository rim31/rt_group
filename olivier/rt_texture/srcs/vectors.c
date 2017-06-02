/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 10:02:14 by svelhinh          #+#    #+#             */
/*   Updated: 2016/05/24 15:23:39 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vector	vecprod(t_vector *v1, t_vector *v2)
{
	t_vector	result;

	result.x = v1->y * v2->z - v1->z * v2->y;
	result.y = v1->z * v2->x - v1->x * v2->z;
	result.z = v1->x * v2->y - v1->y * v2->x;
	return (result);
}

t_vector	vecsub(t_vector *v1, t_vector *v2)
{
	t_vector result;

	result.x = v2->x - v1->x;
	result.y = v2->y - v1->y;
	result.z = v2->z - v1->z;
	return (result);
}

t_vector	vecadd(t_vector *v1, t_vector *v2)
{
	t_vector result;

	result.x = v2->x + v1->x;
	result.y = v2->y + v1->y;
	result.z = v2->z + v1->z;
	return (result);
}

t_vector	vecscale(t_vector *v, double factor)
{
	t_vector result;

	result.x = v->x * factor;
	result.y = v->y * factor;
	result.z = v->z * factor;
	return (result);
}

double		vecdot(t_vector *v1, t_vector *v2)
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

t_vector	normalize(t_vector *v1)
{
	t_vector	res;
	double		vdist;

	vdist = sqrt(vecdot(v1, v1));
	res.x = v1->x / vdist;
	res.y = v1->y / vdist;
	res.z = v1->z / vdist;
	return (res);
}
