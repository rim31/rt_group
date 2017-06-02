/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grass-kw <grass-kw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 10:01:53 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/13 11:35:51 by grass-kw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** vecs[0] = n
** vecs[1] = light
*/

double			specular_light(t_vector vecs[2], t_figure object,
	double ambient, int cel_shading)
{
	double		spec;
	t_vector	r;
	double		vecdot_n_light;
	t_vector	v;

	normalize(&vecs[0]);
	v = new_vector(-2 * vecs[0].x * vecdot(&vecs[0], &vecs[1]), -2 * vecs[0].y *
	vecdot(&vecs[0], &vecs[1]), -2 * vecs[0].z * vecdot(&vecs[0], &vecs[1]));
	normalize(&v);
	vecscale(&vecs[1], -1);
	normalize(&vecs[1]);
	vecdot_n_light = vecdot(&vecs[0], &vecs[1]);
	r = new_vector(vecs[1].x - 2 * vecs[0].x * vecdot_n_light, vecs[1].y - 2 *
		vecs[0].y * vecdot_n_light, vecs[1].z - 2 * vecs[0].z * vecdot_n_light);
	normalize(&r);
	spec = (1 - ambient) * 0.5;
	spec = pow(vecdot(&r, &v), object.material.specular_power);
	if (cel_shading)
		spec = (spec < 0.5) ? (0.0) : (1.0);
	spec = object.material.specular * spec;
	return (spec);
}

static void		light_rotation(t_env *rt, t_figure object, t_light light,
	t_vector *light_ray)
{
	rt->tmp_l_center = rotations(light.center, object.angle.x,
		object.angle.y, object.angle.z);
	rt->tmp_inter = rotations(rt->inter, object.angle.x, object.angle.y,
		object.angle.z);
	rt->tmp_center = rotations(object.center, object.angle.x,
		object.angle.y, object.angle.z);
	if (light.parallel)
	{
		*light_ray = rt->tmp_l_center;
		vecscale(light_ray, -1);
		rt->tmp_rlight = light.center;
		vecscale((&(rt->tmp_rlight)), -1);
	}
	else
	{
		*light_ray = vecsub(&rt->tmp_inter, &rt->tmp_l_center);
		rt->tmp_rlight = vecsub(&rt->inter, &light.center);
	}
}

static void		light_no_rotation(t_env *rt, t_figure object, t_light light,
	t_vector *light_ray)
{
	rt->tmp_l_center = light.center;
	rt->tmp_inter = rt->inter;
	rt->tmp_center = object.center;
	if (light.parallel)
	{
		rt->tmp_rlight = light.center;
		vecscale(&(rt->tmp_rlight), -1);
	}
	else
		rt->tmp_rlight = vecsub(&rt->inter, &light.center);
	*light_ray = rt->tmp_rlight;
}

t_vector		light_rotate(t_env *rt, t_figure object, t_light light)
{
	t_vector	light_ray;

	if (object.name != SPHERE && object.name != PLANE &&
		object.name != TRIANGLE)
		light_rotation(rt, object, light, &light_ray);
	else
		light_no_rotation(rt, object, light, &light_ray);
	return (light_ray);
}

void			color_light(t_env *rt, double spec, t_figure object,
	t_color light)
{
	t_color		tmp_color;
	double		angle;
	double		spec_angle;

	angle = rt->angle * 255;
	spec_angle = spec * rt->angle;
	tmp_color.r = angle * object.color.r;
	tmp_color.g = angle * object.color.g;
	tmp_color.b = angle * object.color.b;
	tmp_color.r = (tmp_color.r > 0xff) ? (0xff) : (tmp_color.r);
	tmp_color.g = (tmp_color.g > 0xff) ? (0xff) : (tmp_color.g);
	tmp_color.b = (tmp_color.b > 0xff) ? (0xff) : (tmp_color.b);
	rt->color.r += tmp_color.r + spec_angle + light.r * angle;
	rt->color.g += tmp_color.g + spec_angle + light.g * angle;
	rt->color.b += tmp_color.b + spec_angle + light.b * angle;
}
