/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 11:48:40 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/12 11:44:10 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				calcul_light(t_env *rt, int i2)
{
	int			i;

	i = 0;
	rt->color = new_color(0, 0, 0);
	while (i < rt->nblight)
	{
		light(rt, rt->object[i2], rt->light[i]);
		i++;
	}
	if (rt->nblight != 0)
	{
		rt->color.r /= rt->nblight;
		rt->color.g /= rt->nblight;
		rt->color.b /= rt->nblight;
	}
	rt->color.r = (rt->color.r > 0xff) ? (0xff) : (rt->color.r);
	rt->color.g = (rt->color.g > 0xff) ? (0xff) : (rt->color.g);
	rt->color.b = (rt->color.b > 0xff) ? (0xff) : (rt->color.b);
	rt->color.r = (rt->color.r < 0) ? (0) : (rt->color.r);
	rt->color.g = (rt->color.g < 0) ? (0) : (rt->color.g);
	rt->color.b = (rt->color.b < 0) ? (0) : (rt->color.b);
}

static gboolean		intersection2(t_env *rt, t_vector ray, t_vector origin,
	int i)
{
	if ((rt->object[i].name == L_SPHERE && limited_sphere(ray,
		rt->object[i], origin, rt)) ||
	(rt->object[i].name == L_CYLINDER && limited_cylinder(ray,
		rt->object[i], origin, rt)) ||
	(rt->object[i].name == L_CONE && limited_cone(ray, rt->object[i]
		, origin, rt)) ||
	(rt->object[i].name == TRIANGLE && triangle(ray, rt->object[i],
		&rt->t, origin)) ||
	(rt->object[i].name == TORUS && torus(ray, rt->object[i], &rt->t
		, origin)) ||
	(rt->object[i].name == ELLIPSOIDE && ellipsoide(ray, rt->object[i],
		&rt->t, origin)) ||
	(rt->object[i].name == PARABOL && parabol(ray, rt->object[i],
		&rt->t, origin)) ||
	(rt->object[i].name == QUADRILATERAL && quadrilateral(ray,
		rt->object[i], &rt->t, origin)) ||
	(rt->object[i].name == CUBE && cube(ray, &rt->object[i], &rt->t,
		origin)))
		return (1);
	return (0);
}

void				intersection(t_env *rt, t_vector ray, t_vector origin)
{
	int			i;

	rt->i2 = -1;
	i = 0;
	rt->t = 200000;
	rt->disk_cy = 0;
	rt->disk_s = 0;
	while (i < rt->nbobj)
	{
		rt->object[i].shadows = 0;
		if ((rt->object[i].name == SPHERE && sphere(ray, rt->object[i],
			&rt->t, rt->eye)) ||
			(rt->object[i].name == PLANE && plane(ray, rt->object[i],
				&rt->t, rt->eye)) ||
			(rt->object[i].name == CYLINDER && cylinder(ray, rt->object[i],
				&rt->t, rt->eye)) ||
			((rt->object[i].name == CONE || rt->object[i].name == HYPERBOL)
				&& cone(ray, rt->object[i],
					&rt->t, rt->eye)) ||
				intersection2(rt, ray, origin, i))
			rt->i2 = i;
		i++;
	}
}
