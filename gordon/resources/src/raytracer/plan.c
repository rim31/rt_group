/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grass-kw <grass-kw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/19 15:49:59 by grass-kw          #+#    #+#             */
/*   Updated: 2016/04/21 06:50:09 by grass-kw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_v1.h"

double plan(t_obj *obj, t_coor *origin, t_coor *v)
{
	double k;

	k = -1 * (((obj->origin.x * origin->x) + (obj->origin.y * origin->y) +
 				(obj->origin.z * origin->z) + obj->size)
				/
				(obj->origin.x * v->x) + (obj->origin.y * v->y) +
				(obj->origin.z * v->z));
	if (k > ZERO)
		return (k);
	return (ZERO);
}
