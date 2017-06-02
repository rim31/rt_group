/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflec_refrac.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/06 11:18:24 by svelhinh          #+#    #+#             */
/*   Updated: 2016/05/20 14:44:35 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	reflections(t_env *rt, t_vector ray, t_vector orig, int rr)
{
	t_vector	n;
	t_vector	tmp_reflect;

	intersection(rt, ray, orig);
	rt->inter = calcul_ptinter(orig, ray, rt->t);
	calcul_light(rt, rt->i2, ray);
	if (rt->i2 != -1)
	{
		if (rt->object[rt->i2].name != PLANE)
			n = vecsub(&rt->object[rt->i2].center, &rt->inter);
		else
			n = rt->object[rt->i2].center;
		n = normalize(&n);
		if ((rt->disk_s == 2 && rt->object[rt->i2].name == L_SPHERE) || (rt->disk_cy == 2 && rt->object[rt->i2].name == L_CYLINDER))
		{
			n.x = 0;
			n.y = 1;
			n.z = 0;
		}
		if (rt->disk_cy == 3 && rt->object[rt->i2].name == L_CYLINDER)
		{
			n.x = 0;
			n.y = -1;
			n.z = 0;
		}
		tmp_reflect.x = ray.x;
		tmp_reflect.y = ray.y;
		tmp_reflect.z = ray.z;
		ray.x = -2 * n.x * vecdot(&n, &tmp_reflect) + tmp_reflect.x;
		ray.y = -2 * n.y * vecdot(&n, &tmp_reflect) + tmp_reflect.y;
		ray.z = -2 * n.z * vecdot(&n, &tmp_reflect) + tmp_reflect.z;
		orig = rt->inter;
	}
	rt->color2.r = rt->color.r * rt->first_reflec + rt->color2.r * (1 - rt->first_reflec);
	rt->color2.g = rt->color.g * rt->first_reflec + rt->color2.g * (1 - rt->first_reflec);
	rt->color2.b = rt->color.b * rt->first_reflec + rt->color2.b * (1 - rt->first_reflec);
	if (rt->i2 != -1 && rr < rt->max_reflect && rt->object[rt->i2].material.shiny)
		reflections(rt, ray, orig, rr + 1);
}

void	refractions(t_env *rt, t_vector ray, t_vector orig, int rr)
{
	double		root;
	t_vector	tmp_refract;
	t_vector	n;
	double		i_refract;

	intersection(rt, ray, orig);
	rt->inter = calcul_ptinter(orig, ray, rt->t);
	calcul_light(rt, rt->i2, ray);
	if (rt->i2 != -1)
	{
		if (rt->object[rt->i2].name != PLANE)
			n = vecsub(&rt->object[rt->i2].center, &rt->inter);
		else
			n = rt->object[rt->i2].center;
		n = normalize(&n);
		if ((rt->disk_s == 2 && rt->object[rt->i2].name == L_SPHERE) || (rt->disk_cy == 2 && rt->object[rt->i2].name == L_CYLINDER))
		{
			n.x = 0;
			n.y = 1;
			n.z = 0;
		}
		if (rt->disk_cy == 3 && rt->object[rt->i2].name == L_CYLINDER)
		{
			n.x = 0;
			n.y = -1;
			n.z = 0;
		}
		if (rt->prev_refr != 0)
			i_refract = rt->object[rt->i2].material.i_refract / rt->prev_refr;
		rt->prev_refr = rt->object[rt->i2].material.i_refract;
		tmp_refract.x = ray.x;
		tmp_refract.y = ray.y;
		tmp_refract.z = ray.z;
		root = 1 + i_refract * i_refract * (vecdot(&tmp_refract, &n) * vecdot(&tmp_refract, &n) - 1);
		root = (root < 0) ? (0) : (root);
		ray.x = i_refract * tmp_refract.x + (i_refract * vecdot(&tmp_refract, &n) - sqrt(root)) * n.x;
		ray.y = i_refract * tmp_refract.y + (i_refract * vecdot(&tmp_refract, &n) - sqrt(root)) * n.y;
		ray.z = i_refract * tmp_refract.z + (i_refract * vecdot(&tmp_refract, &n) - sqrt(root)) * n.z;
		orig = rt->inter;
	}
		rt->color2.r = rt->color.r * rt->first_refrac + rt->color2.r * (1 - rt->first_refrac);
		rt->color2.g = rt->color.g * rt->first_refrac + rt->color2.g * (1 - rt->first_refrac);
		rt->color2.b = rt->color.b * rt->first_refrac + rt->color2.b * (1 - rt->first_refrac);
	if (rt->i2 != -1 && rr < rt->max_refract && rt->object[rt->i2].material.transparent)
		refractions(rt, ray, orig, rr + 1);
}

void	reflec_refrac(t_env *rt, t_vector ray, t_vector orig)
{
	int	rr;

	rr = 0;
	if (rt->object[rt->i2].material.shiny)
	{
		rt->first_reflec = rt->object[rt->i2].material.reflection;
		reflections(rt, ray, orig, rr);
	}
	if (rt->object[rt->i2].material.transparent)
	{
		rr = 0;
		rt->first_refrac = rt->object[rt->i2].material.refraction;
		rt->prev_refr = rt->object[rt->i2].material.i_refract;
		refractions(rt, ray, orig, rr);
	}
}
