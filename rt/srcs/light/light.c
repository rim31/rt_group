/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 10:01:53 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/12 12:30:02 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_vector	calcul_normal2(t_env *rt, t_figure object, t_vector light_ray,
	t_vector n)
{
	t_vector	tmp;
	t_vector	tmp2;

	if (object.name == TRIANGLE || object.name == QUADRILATERAL
		|| object.name == CUBE)
	{
		tmp = vecsub(&object.a, &object.b);
		tmp2 = vecsub(&object.a, &object.c);
		normalize(&tmp);
		normalize(&tmp2);
		n = vecprod(&tmp, &tmp2);
	}
	if (object.name == ELLIPSOIDE)
		vecscale(&n, 0.5);
	if (object.name == TORUS)
		n = normal_torus(rt->inter, object);
	if (object.name == PARABOL)
		n = normale_parab(rt->inter);
	rt->angle = vecdot(&n, &light_ray) / (sqrt(light_ray.x * light_ray.x
		+ light_ray.y * light_ray.y + light_ray.z * light_ray.z) * sqrt(n.x
		* n.x + n.y * n.y + n.z * n.z));
	return (n);
}

static t_vector	calcul_normal(t_env *rt, t_figure object, t_vector light_ray)
{
	t_vector	n;

	n = vecsub(&rt->tmp_center, &rt->tmp_inter);
	n.y = (object.name == CYLINDER || object.name == L_CYLINDER
		|| object.name == CONE || object.name == HYPERBOL
		|| object.name == L_CONE) ? (0) : (n.y);
	n = (object.name == PLANE) ? (rt->tmp_center) : (n);
	if ((rt->disk_s == 2 && object.name == L_SPHERE) || (rt->disk_cy == 2
		&& object.name == L_CYLINDER)
		|| (rt->disk_co == 2 && object.name == L_CONE))
	{
		n.x = 0;
		n.y = 1;
		n.z = 0;
	}
	if ((rt->disk_cy == 3 && object.name == L_CYLINDER)
	|| (rt->disk_co == 3 && object.name == L_CONE))
	{
		n.x = 0;
		n.y = -1;
		n.z = 0;
	}
	return (calcul_normal2(rt, object, light_ray, n));
}

static double	calcul_cel_shading(double angle)
{
	angle = (angle < 0.2) ? (0) : (angle);
	angle = (angle >= 0.2 && angle < 0.4) ? (0.2) :
				(angle);
	angle = (angle >= 0.4 && angle < 0.5) ? (0.4) :
				(angle);
	angle = (angle >= 0.5) ? (1) : (angle);
	return (angle);
}

void			light(t_env *rt, t_figure object, t_light light)
{
	t_vector	n;
	t_vector	light_ray;
	double		spec;
	t_vector	vecs[2];

	light_ray = light_rotate(rt, object, light);
	if (!shadows(rt, rt->tmp_rlight, rt->inter))
	{
		n = calcul_normal(rt, object, light_ray);
		if (rt->cel_shading)
			rt->angle = calcul_cel_shading(rt->angle);
		if (rt->angle > 0.0001)
		{
			vecs[0] = n;
			vecs[1] = light_ray;
			spec = specular_light(vecs, object, rt->ambient, rt->cel_shading);
			color_light(rt, spec, object, light.color);
		}
	}
}
