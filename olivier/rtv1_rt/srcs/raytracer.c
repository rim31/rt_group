/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 11:48:40 by svelhinh          #+#    #+#             */
/*   Updated: 2016/04/27 19:11:36 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static	void	intersection(t_env *rt, t_vector ray)
{
	int			i;
	int			i2;
	t_vector	inter;

	i2 = -1;
	i = 0;
	rt->final_color = 0;
	while (i < rt->nbobj)
	{
		if ((rt->object[i].name == SPHERE && sphere(ray, rt->object[i], &rt->t, rt->eye)) ||
			(rt->object[i].name == PLANE && plane(ray, rt->object[i], &rt->t, rt->eye)) ||
			(rt->object[i].name == CYLINDER && cylinder(ray, rt->object[i], &rt->t, rt->eye)) ||
			(rt->object[i].name == CONE && cone(ray, rt->object[i], &rt->t, rt->eye)))
				i2 = i;
		i++;
	}
	if (i2 != -1)
	{
		i = 0;
		inter = calcul_ptinter(rt->eye, ray, rt->t);
		rt->color.r = 0;
		rt->color.g = 0;
		rt->color.b = 0;
		while (i < rt->nblight)
		{
			light(rt, rt->object[i2], rt->light[i], inter);
			i++;
		}
		rt->color.r /= rt->nblight;
		rt->color.g /= rt->nblight;
		rt->color.b /= rt->nblight;
		rt->color.r = (rt->color.r > 0xff) ? (0xff) : (rt->color.r);
		rt->color.g = (rt->color.g > 0xff) ? (0xff) : (rt->color.g);
		rt->color.b = (rt->color.b > 0xff) ? (0xff) : (rt->color.b);
		rt->final_color = (int)rt->color.r * 0x10000 + (int)rt->color.g * 0x100 + (int)rt->color.b;
	}
}

void		raytracer(t_env *rt)
{
	int			x;
	int			y;
	int			pas;
	t_vector	ray;

	y = 0;
	pas = 1;
	if (rt->keyup == 1 || rt->keydown == 1 || rt->keyleft == 1 || rt->keyright == 1)
		pas = rt->w / 640 + rt->h / 480;
	while (y < rt->h)
	{
		x = 0;
		while (x < rt->w)
		{
			ray.x = x - rt->w / 2 - rt->eye.x + rt->xx;
			ray.y = y - rt->h / 2 - rt->eye.y;
			ray.z = rt->w - rt->eye.z + rt->zz;
			ray = rotations(ray, rt->cam_angle.x, rt->cam_angle.y, rt->cam_angle.z);
			rt->t = 200000;
			intersection(rt, ray);
			mlx_pixel_put_to_image(rt->final_color, rt, x, y);
			x += pas;
		}
		y += pas;
	}
}
