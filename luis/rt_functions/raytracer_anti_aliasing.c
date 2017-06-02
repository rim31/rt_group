/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer_anti_aliasing.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 19:02:16 by lnieto-m          #+#    #+#             */
/*   Updated: 2016/04/28 19:04:22 by lnieto-m         ###   ########.fr       */
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

static int	average_color(int x, int y, t_color **aliasing_tab)
{
	t_color		average;

	average.r = (aliasing_tab[y][x].r + aliasing_tab[y][x + 1].r
				+ aliasing_tab[y + 1][x].r + aliasing_tab[y + 1][x + 1].r) / 4;
	average.g = (aliasing_tab[y][x].g + aliasing_tab[y][x + 1].g
				+ aliasing_tab[y + 1][x].g + aliasing_tab[y + 1][x + 1].g) / 4;
	average.b = (aliasing_tab[y][x].b + aliasing_tab[y][x + 1].b
				+ aliasing_tab[y + 1][x].b + aliasing_tab[y + 1][x + 1].b) / 4;
	return ((int)average.r * 0x10000 + (int)average.g * 0x100 + (int)average.b);
}

static void	image_render(t_color **aliasing_tab, t_env *rt, double y)
{
	int		x;
	int		x_aliasing;
	int		y_aliasing;

	x = 0;
	x_aliasing = 0;
	y_aliasing = rt->start_h;
	while (y < rt->end_h)
	{
		x = 0;
		x_aliasing = 0;
		while (x < rt->w)
		{
			mlx_pixel_put_to_image(average_color(x_aliasing, y_aliasing, aliasing_tab), rt, x, y);
			x++;
			x_aliasing += 2;
		}
		y++;
		y_aliasing += 2;
	}
}

void		*raytracer(void *arg)
{
	double		x;
	double		y;
	int			x_aliasing;
	int			y_aliasing;
	double		pas;
	t_vector	ray;
	t_env		*rt;
	t_color		**aliasing_tab;
	int			i;

	rt = (t_env *)arg;
	y = rt->start_h;
	pas = 0.5;
	x_aliasing = 0;
	y_aliasing = rt->start_h;
	i = 0;
	if (!(aliasing_tab = (t_color **)malloc(sizeof(t_color *) * (int)(rt->end_h) * 2)))
		pthread_exit(0);
	while (i < rt->end_h * 2)
	{
		if (!(aliasing_tab[i] = (t_color *)malloc(sizeof(t_color) * rt->w * 2)))
			pthread_exit(0);
		i++;
	}
	while (y < rt->end_h)
	{
		x = 0;
		x_aliasing = 0;
		while (x < rt->w)
		{
			ray.x = x - rt->w / 2 - rt->eye.x + rt->xx;
			ray.y = y - rt->h / 2 - rt->eye.y;
			ray.z = rt->w - rt->eye.z + rt->zz;
			ray = rotations(ray, rt->cam_angle.x, rt->cam_angle.y, rt->cam_angle.z);
			rt->t = 200000;
			intersection(rt, ray);
			aliasing_tab[y_aliasing][x_aliasing] = rt->color;
			x_aliasing++;
			x += pas;
		}
		y += pas;
		y_aliasing++;
	}
	y = rt->start_h;
	image_render(aliasing_tab, rt, y);
	pthread_exit(0);
}
