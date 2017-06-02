/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grass-kw <grass-kw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/19 15:41:11 by grass-kw          #+#    #+#             */
/*   Updated: 2016/04/22 22:16:32 by grass-kw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_v1.h"

double			sphere(t_obj *obj, t_coor *origin, t_coor *v)
{
	double a;
	double b;
	double c;
	double delta;

	a = pow(v->x, 2) + pow(v->y, 2) + pow(v->z, 2);
	b = 2 * (((origin->x - obj->origin.x) * v->x) +
		((origin->y - obj->origin.y) * v->y) +
		((origin->z - obj->origin.z) * v->z));
	c = pow(origin->x, 2) + pow(origin->y, 2) + pow(origin->z, 2) - pow(obj->size, 2);
	delta = pow(b, 2) - (4 * a * c);
	return (resolve(delta, a, b));
}
