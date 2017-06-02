/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 11:48:40 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/03 12:39:04 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		calcul_light(t_env *rt, int i2, t_vector ray)
{
	int			i;
	t_light		light_tmp;

	i = 0;
	rt->color.r = 0;
	rt->color.g = 0;
	rt->color.b = 0;
	while (i < rt->nblight)
	{
		light_tmp = rt->light[i];
		light(rt, rt->object[i2], light_tmp, ray);
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

void	intersection(t_env *rt, t_vector ray, t_vector origin)
{
	int			i;

	rt->i2 = -1;
	i = 0;
	rt->t = 200000;
	rt->disk_cy = 0;
	rt->disk_s = 0;
	while (i < rt->nbobj)
	{
		if (!rt->object[i].negativ)
			if ((rt->object[i].name == SPHERE && sphere(ray, rt->object[i], &rt->t,
					origin)) ||
				(rt->object[i].name == PLANE && plane(ray, rt->object[i], &rt->t,
					origin)) ||
				(rt->object[i].name == CYLINDER && cylinder(ray, rt->object[i],
					&rt->t, origin, rt)) ||
				((rt->object[i].name == CONE || rt->object[i].name == HYPERBOL) && cone(ray, rt->object[i], &rt->t,
					origin)) ||
				(rt->object[i].name == L_SPHERE && limited_sphere(ray, rt->object[i], &rt->t,
					origin, &rt->disk_s)) ||
				(rt->object[i].name == L_CYLINDER && limited_cylinder(ray, rt->object[i], &rt->t,
					origin, &rt->disk_cy)) ||
				(rt->object[i].name == L_CONE && limited_cone(ray, rt->object[i], &rt->t,
					origin, &rt->disk_co)) ||
				(rt->object[i].name == TRIANGLE && triangle(ray, rt->object[i], &rt->t,
					origin)) ||
				(rt->object[i].name == QUADRILATERAL && quadrilateral(ray, rt->object[i], &rt->t,
					origin)))
				rt->i2 = i;
		i++;
	}
}

static void		scan(int pas, t_env *rt)
{
	int			x;
	int			y;
	double		diffuse;
	t_vector	ray;
	t_color		color3;
	t_figure	object;

	y = rt->start_h;
	diffuse = (1 - rt->ambient) * 0.5;
	while (y < rt->end_h)
	{
		x = 0;
		while (x < rt->w)
		{
			ray.x = x - rt->w / 2 - rt->eye.x + rt->xx;
			ray.y = y - rt->h / 2 - rt->eye.y;
			ray.z = rt->w - rt->eye.z + rt->zz;
			ray = rotations(ray, rt->cam_angle.x, rt->cam_angle.y,
				rt->cam_angle.z);
			ray = normalize(&ray);
			intersection(rt, ray, rt->eye);
			rt->color2.r = rt->bg_color.r * 255;
			rt->color2.g = rt->bg_color.g * 255;
			rt->color2.b = rt->bg_color.b * 255;
			if (rt->i2 != -1)
			{
				object = rt->object[rt->i2];
				// if (object.name == SPHERE)
				// {
				// 	double n = perlin(rt->inter, 0.5, 0.5, 25);
				// 	// printf("%f\n", perlin(rt->inter.x, rt->inter.y, rt->inter.z, 2, 2, 5));
				// 	if (n <= -1)
				// 	{
				// 		object.color.r = 0;
				// 		object.color.g = 1;
				// 		object.color.b = 0;
				// 	}
				// 	else if (n > -1 && n <= 0)
				// 	{
				// 		object.color.r = 0;
				// 		object.color.g = 0.7;
				// 		object.color.b = 0;
				// 	}
				// 	else if (n > 0 && n <= 1)
				// 	{
				// 		object.color.r = 0;
				// 		object.color.g = 0.4;
				// 		object.color.b = 0;
				// 	}
				// 	else if (n > 1)
				// 	{
				// 		object.color.r = 0;
				// 		object.color.g = 0;
				// 		object.color.b = 0.7;
				// 	}
				// }
				rt->inter = calcul_ptinter(rt->eye, ray, rt->t);
				calcul_light(rt, rt->i2, ray);
				rt->color2 = rt->color;
				reflec_refrac(rt, ray, rt->eye);
				color3.r = object.color.r * 255;
				color3.g = object.color.g * 255;
				color3.b = object.color.b * 255;
			}
			rt->color2.r *= diffuse;
			rt->color2.g *= diffuse;
			rt->color2.b *= diffuse;
			color3.r *= rt->ambient;
			color3.g *= rt->ambient;
			color3.b *= rt->ambient;
			rt->color2.r += color3.r;
			rt->color2.g += color3.g;
			rt->color2.b += color3.b;
			if (rt->filter)
				rt->color2 = color_filter(rt->color2, rt->filter_color);
			rt->final_color = (int)rt->color2.r * 0x10000 + (int)rt->color2.g * 0x100
				+ (int)rt->color2.b;
			mlx_pixel_put_to_image(rt->final_color, rt, x, y);
			x += pas;
		}
		y += pas;
	}
}

void			*raytracer(void *arg)
{
	int		pas;
	t_env	*rt;

	rt = (t_env *)arg;
	pas = 1;
	if (rt->keyup == 1 || rt->keydown == 1 || rt->keyleft == 1
		|| rt->keyright == 1)
		pas = 2;
	scan(pas, rt);
	pthread_exit(0);
}
