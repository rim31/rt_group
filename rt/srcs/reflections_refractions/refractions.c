/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refractions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/06 11:18:24 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/12 11:45:31 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		calcul_refrac(t_env *rt, t_vector *n)
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
}

static void		calcul_refrac_if(t_env *rt, t_vector *ray, t_vector *orig,
	double i_refract)
{
	double		root;
	t_vector	n;
	t_vector	tmp_refract;

	if (rt->i2 != -1)
	{
		calcul_refrac(rt, &n);
		if (rt->prev_refr != 0)
			i_refract = rt->object[rt->i2].material.i_refract / rt->prev_refr;
		rt->prev_refr = rt->object[rt->i2].material.i_refract;
		tmp_refract.x = ray->x;
		tmp_refract.y = ray->y;
		tmp_refract.z = ray->z;
		root = 1 + i_refract * i_refract * (vecdot(&tmp_refract, &n) *
		vecdot(&tmp_refract, &n) - 1);
		root = (root < 0) ? (0) : (root);
		ray->x = i_refract * tmp_refract.x + (i_refract *
			vecdot(&tmp_refract, &n) - sqrt(root)) * n.x;
		ray->y = i_refract * tmp_refract.y + (i_refract *
			vecdot(&tmp_refract, &n) - sqrt(root)) * n.y;
		ray->z = i_refract * tmp_refract.z + (i_refract *
			vecdot(&tmp_refract, &n) - sqrt(root)) * n.z;
		*orig = rt->inter;
	}
}

void			refractions(t_env *rt, t_vector ray, t_vector orig, int rr)
{
	double		i_refract;

	intersection(rt, ray, orig);
	rt->inter = calcul_ptinter(orig, ray, rt->t);
	calcul_light(rt, rt->i2);
	i_refract = 0;
	calcul_refrac_if(rt, &ray, &orig, i_refract);
	rt->color2.r = rt->color.r * rt->first_refrac + rt->color2.r *
	(1 - rt->first_refrac);
	rt->color2.g = rt->color.g * rt->first_refrac + rt->color2.g *
	(1 - rt->first_refrac);
	rt->color2.b = rt->color.b * rt->first_refrac + rt->color2.b *
	(1 - rt->first_refrac);
	if (rt->i2 != -1 && rr < rt->max_refract &&
		rt->object[rt->i2].material.transparent)
		refractions(rt, ray, orig, rr + 1);
}
