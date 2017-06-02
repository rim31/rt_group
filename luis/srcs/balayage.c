/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   balayage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/05 16:26:20 by lnieto-m          #+#    #+#             */
/*   Updated: 2016/04/20 17:57:16 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		balayage5(t_env *e)
{
	t_point		p;
	t_vector	ray;

	p.x = 0;
	p.y = 0;
	while (p.y++ < HEIGHT)
	{
		while (p.x++ < WIDTH)
		{
			ray = rotation(rays(p), e->rot_cam);
			cone(ray, e, e->cone, shadow2);
			sphere(ray, e, e->sphere1, shadow2);
			sphere(ray, e, e->sphere3, shadow2);
			sphere(ray, e, e->sphere2, shadow2);
			plan(ray, e, e->plan2, shadow2);
			plan(ray, e, e->plan1, shadow2);
			cylindre(ray, e, e->cylindre, shadow2);
			mlx_pixel_put_to_image(p.x, p.y, e);
			e->color = 0;
			e->k = -1;
		}
		p.x = 0;
	}
}

void		balayage4(t_env *e)
{
	t_point		p;
	t_vector	ray;

	p.x = 0;
	p.y = 0;
	while (p.y++ < HEIGHT)
	{
		while (p.x++ < WIDTH)
		{
			ray = rotation(rays(p), e->rot_cam);
			sphere(ray, e, e->sphere1, shadow);
			mlx_pixel_put_to_image(p.x, p.y, e);
			e->color = 0;
			e->k = -1;
		}
		p.x = 0;
	}
}

void		balayage3(t_env *e)
{
	t_point		p;
	t_vector	ray;

	p.x = 0;
	p.y = 0;
	while (p.y++ < HEIGHT)
	{
		while (p.x++ < WIDTH)
		{
			ray = rotation(rays(p), e->rot_cam);
			cylindre(ray, e, e->cylindre, shadow);
			mlx_pixel_put_to_image(p.x, p.y, e);
			e->color = 0;
			e->k = -1;
		}
		p.x = 0;
	}
}

void		balayage2(t_env *e)
{
	t_point		p;
	t_vector	ray;

	p.x = 0;
	p.y = 0;
	while (p.y++ < HEIGHT)
	{
		while (p.x++ < WIDTH)
		{
			ray = rotation(rays(p), e->rot_cam);
			cone(ray, e, e->cone, shadow);
			plan(ray, e, e->plan1, shadow);
			mlx_pixel_put_to_image(p.x, p.y, e);
			e->color = 0;
			e->k = -1;
		}
		p.x = 0;
	}
}

void		balayage1(t_env *e)
{
	t_point		p;
	t_vector	ray;

	p.x = 0;
	p.y = 0;
	while (p.y++ < HEIGHT)
	{
		while (p.x++ < WIDTH)
		{
			ray = rotation(rays(p), e->rot_cam);
			cone(ray, e, e->cone, shadow);
			sphere(ray, e, e->sphere1, shadow);
			plan(ray, e, e->plan2, shadow);
			plan(ray, e, e->plan1, shadow);
			cylindre(ray, e, e->cylindre, shadow);
			mlx_pixel_put_to_image(p.x, p.y, e);
			e->color = 0;
			e->k = -1;
		}
		p.x = 0;
	}
}
