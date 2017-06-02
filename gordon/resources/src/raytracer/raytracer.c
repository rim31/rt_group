/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grass-kw <grass-kw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/10 07:48:31 by grass-kw          #+#    #+#             */
/*   Updated: 2016/04/24 19:44:48 by grass-kw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_v1.h"

static void	initialise_env(t_env *e)
{
	e->k = ZERO;
	e->inter = 0;
}

static void	parametric_vector(t_env *e)
{
	e->parametric_vector->x = e->camera.origin.x + (e->k) * (e->v.x);
	e->parametric_vector->y = e->camera.origin.y + (e->k) * (e->v.y);
	e->parametric_vector->z = e->camera.origin.z + (e->k) * (e->v.z);
}

static void	normalize_spots(t_env *e)
{
	t_list	*cursor;
	t_obj	*spot;

	cursor = e->list_spot;
	while (cursor)
	{
		spot = (t_obj *)cursor->content;
		spot->l.x = spot->origin.x - e->parametric_vector->x;
		spot->l.y = spot->origin.y - e->parametric_vector->y;
		spot->l.z = spot->origin.z - e->parametric_vector->z;
		cursor = cursor->next;
	}
}

t_color		raytracer(t_env *e, int i, int j)
{
	t_color	color;

	color = set_rgb(0, 0, 0);
	color = raytracing_obj(e, i, j);
	if (e->inter && e->list_spot != NULL)
	{
		parametric_vector(e);
		normalize_spots(e);
		if (shadow(e, &color) != 1 && e->list_spot != NULL)
			color = brightness(e, color);
	}
	initialise_env(e);
	return (color);
}
