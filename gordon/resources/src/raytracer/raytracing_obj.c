/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing_obj.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grass-kw <grass-kw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 14:08:04 by grass-kw          #+#    #+#             */
/*   Updated: 2016/04/24 15:04:18 by grass-kw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_v1.h"

static void	normalize(t_env *e, int i, int j)
{
	e->v = set_coord(100, LENGHT / 2 - i, WIDTH / 2 - j);
	rotation(&(e->v), e->camera.angle);
}

t_color	intersection_obj_eye(t_env *e)
{
	t_list	*tmp;
	double	result;
	t_color	color;
	t_obj	*obj;
	double	k;

	k = ZERO;
	tmp = e->list_obj;
	while (tmp)
	{
		obj = (t_obj *)tmp->content;
		result = intersection(obj, &(e->camera.origin), &(e->v));
		if ((result > ZERO) && ((k == ZERO) || (k > result)))
		{
			k = result;
			e->k = result;
			e->inter = 1;
			color = obj->color;
			e->obj_inter = obj;
		}
		tmp = tmp->next;
	}
	return (color);
}

t_color	raytracing_obj(t_env *e, int i, int j)
{
	t_color	color;

	normalize(e, i, j);
	color = intersection_obj_eye(e);
	return (color);
}
