/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <oseng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 10:01:53 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/07 15:56:37 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		shadows(t_env *rt, t_vector ray_light, t_vector inter)
{
	int			i;
	double		t;
	int			disk;

	i = 0;
	t = 1;
	disk = 0;
	while (i < rt->nbobj)
	{
		if (!rt->object[i].negativ)
			if ((rt->object[i].name == SPHERE && sphere(ray_light, rt->object[i],
					&t, inter)) ||
				(rt->object[i].name == PLANE && plane(ray_light,
					rt->object[i], &t, inter)) ||
				(rt->object[i].name == CYLINDER && cylinder(ray_light,
					rt->object[i], &t, inter, rt)) ||
				((rt->object[i].name == CONE || rt->object[i].name == HYPERBOL) && cone(ray_light, rt->object[i], &t,
					inter)) ||
				(rt->object[i].name == L_SPHERE && limited_sphere(ray_light, rt->object[i], &t,
					inter, &disk)) ||
				(rt->object[i].name == L_CYLINDER && limited_cylinder(ray_light, rt->object[i], &t,
					inter, &disk)) ||
				(rt->object[i].name == L_CONE && limited_cone(ray_light, rt->object[i], &t,
					inter, &disk)) ||
				(rt->object[i].name == TRIANGLE && triangle(ray_light, rt->object[i], &t,
					inter)) ||
				(rt->object[i].name == QUADRIC && quadric(ray_light, rt->object[i], &t,
					inter)) ||
				(rt->object[i].name == TORUS && torus(ray_light, rt->object[i], &t,
					inter)) ||
				(rt->object[i].name == QUADRILATERAL && quadrilateral(ray_light, rt->object[i], &t,
					inter)))
				return (1);
		i++;
	}
	return (0);
}

static double	specular_light(t_vector n, t_vector light, t_figure object,
	t_vector ray, double ambient)
{
	double		spec;
	t_vector	r;

	ray = normalize(&ray);
	light = vecscale(&light, -1);
	ray = normalize(&light);
	r.x = light.x - 2 * n.x * vecdot(&n, &light);
	r.y = light.y - 2 * n.y * vecdot(&n, &light);
	r.z = light.z - 2 * n.z * vecdot(&n, &light);
	r = normalize(&r);
	spec = (1 - ambient) * 0.5;
	spec = object.material.specular * spec * pow(vecdot(&r, &ray), object.material.specular_power);
	return (spec);
}

static t_vector	light_rotate(t_env *rt, t_figure object, t_light light)
{
	t_vector	light_ray;

	if (object.name != SPHERE && object.name != PLANE && object.name != TRIANGLE)
	{
		rt->tmp_l_center = rotations(light.center, object.angle.x,
			object.angle.y, object.angle.z);
		rt->tmp_inter = rotations(rt->inter, object.angle.x, object.angle.y,
			object.angle.z);
		rt->tmp_center = rotations(object.center, object.angle.x,
			object.angle.y, object.angle.z);
		light_ray = vecsub(&rt->tmp_inter, &rt->tmp_l_center);
		rt->tmp_rlight = vecsub(&rt->inter, &light.center);
	}
	else
	{
		rt->tmp_l_center = light.center;
		rt->tmp_inter = rt->inter;
		rt->tmp_center = object.center;
		rt->tmp_rlight = vecsub(&rt->inter, &light.center);
		light_ray = rt->tmp_rlight;
	}
	return (light_ray);
}

static void		color_light(t_env *rt, double spec, t_figure object,
	t_color light)
{
	t_color		tmp_color;

	tmp_color.r = rt->angle * object.color.r * 255;
	tmp_color.g = rt->angle * object.color.g * 255;
	tmp_color.b = rt->angle * object.color.b * 255;
	tmp_color.r = (tmp_color.r > 0xff) ? (0xff) : (tmp_color.r);
	tmp_color.g = (tmp_color.g > 0xff) ? (0xff) : (tmp_color.g);
	tmp_color.b = (tmp_color.b > 0xff) ? (0xff) : (tmp_color.b);
	rt->color.r += tmp_color.r + spec * rt->angle + 255 * light.r * rt->angle;
	rt->color.g += tmp_color.g + spec * rt->angle + 255 * light.g * rt->angle;
	rt->color.b += tmp_color.b + spec * rt->angle + 255 * light.b * rt->angle;
}
/*
** float a;
** float b;
**
**
** a = 2;
** b = 1;
**
**
** n.x = 4 * i.x * (i.x * i.x + i.y * i.y + i.z * i.z - (a * a + b * b));
** n.y = 4 * i.y * (i.x * i.x + i.y * i.y + i.z * i.z - (a * a + b * b) + 2 * a * a);
** n.z =  4 * i.z * (i.x * i.x + i.y * i.y + i.z * i.z - (a * a + b * b));
*/


t_vector normal_torus(t_vector inter)
{
	t_vector n;

	n.x = 2 * inter.x;
	n.y = -2 * inter.y;
	n.z = 2 * inter.z;
	return(n);
}

t_vector normal_quadric(t_vector inter)
{
	t_vector n;
	float a;
	float b;
	float c;
	float d;
	float e;
	float f;
	float g;
	float h;
	float i;

	a = 10;
	b = 10;
	c = 10;
	d = 0;
	e = 0;
	f = 10;
	g = -10;
	h = 10;
	i = 0;

	n.x = 2 * a * inter.x + d * inter.y + e * inter.z + g;
	n.y = 2 * b * inter.y + d * inter.x + f * inter.z + h;
	n.z = 2 * c * inter.z + e * inter.x + f * inter.y + i;
	return(n);
}

void			light(t_env *rt, t_figure object, t_light light, t_vector ray)
{
	t_vector	n;
	t_vector	light_ray;
	double		spec;

	light_ray = light_rotate(rt, object, light);
	if (!shadows(rt, rt->tmp_rlight, rt->inter))
	{
		n = vecsub(&rt->tmp_center, &rt->tmp_inter);
		n.y = (object.name == CYLINDER || object.name == L_CYLINDER || object.name == CONE || object.name == HYPERBOL || object.name == L_CONE) ? (0) : (n.y);
		n = (object.name == PLANE) ? (rt->tmp_center) : (n);
		if ((rt->disk_s == 2 && object.name == L_SPHERE) || (rt->disk_cy == 2 && object.name == L_CYLINDER) || (rt->disk_co == 2 && object.name == L_CONE))
		{
			n.x = 0;
			n.y = 1;
			n.z = 0;
		}
		if ((rt->disk_cy == 3 && object.name == L_CYLINDER) || (rt->disk_co == 3 && object.name == L_CONE))
		{
			n.x = 0;
			n.y = -1;
			n.z = 0;
		}
		if (object.name == TRIANGLE/* || object.name == QUADRILATERAL*/)
		{
			t_vector tmp;
			t_vector tmp2;

			tmp = vecsub(&object.a, &object.b);
			tmp2 = vecsub(&object.a, &object.c);
			tmp = normalize(&tmp);
			tmp2 = normalize(&tmp2);
			n = vecprod(&tmp, &tmp2);
		}
		if (object.name == QUADRIC)
			n = normal_quadric(rt->inter);
		if (object.name == TORUS)
				n = normal_torus(rt->inter);
		rt->angle = vecdot(&n, &light_ray) / (sqrt(pow(light_ray.x, 2)
		+ pow(light_ray.y, 2) + pow(light_ray.z, 2)) * sqrt(pow(n.x, 2)
		+ pow(n.y, 2) + pow(n.z, 2)));
		if (rt->angle > 0.0001)
		{
			spec = specular_light(n, light_ray, object, ray, rt->ambient);
			color_light(rt, spec, object, light.color);
		}
	}
}
