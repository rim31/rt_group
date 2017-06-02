/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grass-kw <grass-kw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/22 23:30:00 by grass-kw          #+#    #+#             */
/*   Updated: 2016/04/22 23:36:32 by grass-kw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_v1.h"

double intersection(t_obj *obj, t_coor *camera, t_coor *v)
{
	double result;

	if (obj->type == SPHERE)
		result = sphere(obj, camera, v);
	if (obj->type == PLAN)
		result = plan(obj, camera, v);
	if (obj->type == CYLINDRE)
		result = cylindre(obj, camera, v);
	if (obj->type == CONE)
		result = cone(obj, camera, v);
	return (result);
}