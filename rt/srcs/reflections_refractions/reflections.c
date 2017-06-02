/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/06 11:18:24 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/12 19:13:18 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	calcul_reflec(t_env *rt, t_vector *n, t_vector *tmp_reflect,
	t_vector *ray)
{
	if (rt->object[rt->i2].name != PLANE)
		*n = vecsub(&rt->object[rt->i2].center, &rt->inter);
	else
		*n = rt->object[rt->i2].center;
	normalize(n);
	if ((rt->disk_s == 2 && rt->object[rt->i2].name == L_SPHERE) ||
	(rt->disk_cy == 2 && rt->object[rt->i2].name == L_CYLINDER))
	{
		n->x = 0;
		n->y = 1;
		n->z = 0;
	}
	if (rt->disk_cy == 3 && rt->object[rt->i2].name == L_CYLINDER)
	{
		n->x = 0;
		n->y = -1;
		n->z = 0;
	}
	tmp_reflect->x = ray->x;
	tmp_reflect->y = ray->y;
	tmp_reflect->z = ray->z;
	ray->x = -2 * n->x * vecdot(n, tmp_reflect) + tmp_reflect->x;
	ray->y = -2 * n->y * vecdot(n, tmp_reflect) + tmp_reflect->y;
	ray->z = -2 * n->z * vecdot(n, tmp_reflect) + tmp_reflect->z;
}

void		reflections(t_env *rt, t_vector ray, t_vector orig, int rr)
{
	t_vector	n;
	t_vector	tmp_reflect;

	intersection(rt, ray, orig);
	rt->inter = calcul_ptinter(orig, ray, rt->t);
	calcul_light(rt, rt->i2);
	if (rt->i2 != -1)
	{
		calcul_reflec(rt, &n, &tmp_reflect, &ray);
		orig = rt->inter;
	}
	rt->color2.r = rt->color.r * rt->first_reflec + rt->color2.r *
	(1 - rt->first_reflec);
	rt->color2.g = rt->color.g * rt->first_reflec + rt->color2.g *
	(1 - rt->first_reflec);
	rt->color2.b = rt->color.b * rt->first_reflec + rt->color2.b *
	(1 - rt->first_reflec);
	if (rt->i2 != -1 && rr < rt->max_reflect &&
		rt->object[rt->i2].material.shiny)
		reflections(rt, ray, orig, rr + 1);
}
