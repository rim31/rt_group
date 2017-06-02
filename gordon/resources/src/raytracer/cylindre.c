/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylindre.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grass-kw <grass-kw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/19 15:39:19 by grass-kw          #+#    #+#             */
/*   Updated: 2016/04/21 06:52:11 by grass-kw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_v1.h"

double			cylindre(t_obj *obj, t_coor *origin, t_coor *v)
{
	double a;
	double b;
	double c;
	double delta;

	rotation(&(obj->origin), obj->angle);
	rotation(origin, obj->angle);
	rotation(v, obj->angle);
	a = pow(v->x, 2) + pow(v->y, 2);
	b = 2 * (((origin->x - obj->origin.x) * v->x) +
		((origin->y - obj->origin.y) * v->y));
	c = pow(origin->x, 2) + pow(origin->y, 2) - pow(obj->size, 2);
	delta = pow(b, 2) - (4 * a * c);
	rotation_inverse(&(obj->origin), obj->angle);
	rotation_inverse(origin, obj->angle);
	rotation_inverse(v, obj->angle);
	return (resolve(delta, a, b));
}
