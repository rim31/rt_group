/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 11:48:40 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/13 15:51:30 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			calcul_final_color(t_env *rt, t_color **tab)
{
	rt->color3.r *= rt->ambient;
	rt->color3.g *= rt->ambient;
	rt->color3.b *= rt->ambient;
	rt->color2.r *= rt->diffuse;
	rt->color2.g *= rt->diffuse;
	rt->color2.b *= rt->diffuse;
	rt->color2.r += rt->color3.r;
	rt->color2.g += rt->color3.g;
	rt->color2.b += rt->color3.b;
	if (rt->filter)
		rt->color2 = color_filter(rt->color2, rt->filter_color);
	if (rt->antialiasing > 0)
	{
		tab[rt->y_aliasing][rt->x_aliasing] = rt->color2;
		rt->x_aliasing++;
	}
	else
	{
		rt->final_color = (int)rt->color2.r * 0x10000 +
		(int)rt->color2.g * 0x100 + (int)rt->color2.b;
		mlx_pixel_put_to_image(rt->final_color, rt, rt->x, rt->y);
	}
}

static void			calcul_color(t_env *rt, t_vector *ray, t_color first_color)
{
	ray->x = rt->x - rt->w / 2 - rt->eye.x;
	ray->y = rt->y - rt->h / 2 - rt->eye.y;
	ray->z = rt->w - rt->eye.z;
	*ray = rotations(*ray, rt->cam_angle.x, rt->cam_angle.y,
			rt->cam_angle.z);
	normalize(ray);
	intersection(rt, *ray, rt->eye);
	rt->color2 = first_color;
	if (rt->i2 != -1)
	{
		rt->inter = calcul_ptinter(rt->eye, *ray, rt->t);
		if (rt->object[rt->i2].material.texture.path[0] != '\0' ||
			rt->object[rt->i2].material.procedural.active)
			rt->object[rt->i2].color = textures(
				rt->object[rt->i2].material.texture.buffer,
					rt->object[rt->i2], rt->inter);
		calcul_light(rt, rt->i2);
		rt->color2 = rt->color;
		reflec_refrac(rt, *ray, rt->eye);
		rt->color3.r = rt->object[rt->i2].color.r * 255;
		rt->color3.g = rt->object[rt->i2].color.g * 255;
		rt->color3.b = rt->object[rt->i2].color.b * 255;
	}
	else
		rt->color3 = rt->bg_color;
}

static t_color		**init_antialiasing(t_env *rt, t_color *first_color,
	double *pas)
{
	t_color		**tab;

	tab = NULL;
	rt->y_aliasing = 0;
	if (rt->antialiasing > 0)
	{
		tab = create_aliasing_tab(rt, rt->antialiasing);
		if (!tab)
			ft_exit("Allocation failed");
		*pas = 1 / sqrt(rt->antialiasing);
	}
	rt->diffuse = (1 - rt->ambient) * 0.5;
	*first_color = new_color(rt->bg_color.r * 255, rt->bg_color.g * 255,
		rt->bg_color.b * 255);
	return (tab);
}

static void			scan(double pas, t_env *rt)
{
	t_color			**tab;
	t_vector		ray;
	t_color			first_color;

	rt->y = rt->start_h;
	tab = init_antialiasing(rt, &first_color, &pas);
	while (rt->y < rt->end_h)
	{
		rt->x = 0;
		rt->x_aliasing = 0;
		while (rt->x < rt->w)
		{
			calcul_color(rt, &ray, first_color);
			calcul_final_color(rt, tab);
			rt->x += pas;
		}
		rt->y += pas;
		rt->y_aliasing++;
	}
	rt->y = rt->start_h;
	if (rt->antialiasing)
	{
		aliasing_render(tab, rt, rt->y);
		free_aliasing_tab(tab, rt, rt->antialiasing);
	}
}

void				*raytracer(void *args)
{
	t_env	*rt;

	rt = (t_env *)args;
	scan(1, rt);
	pthread_exit(0);
}
