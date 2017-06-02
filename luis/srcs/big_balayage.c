/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_balayage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/20 11:47:09 by lnieto-m          #+#    #+#             */
/*   Updated: 2016/04/20 16:49:41 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	big_balayage2(t_env *e, t_vector ray)
{
	sphere(ray, e, e->sphere, big_shadow);
	sphere(ray, e, e->sphere1, big_shadow);
	sphere(ray, e, e->sphere2, big_shadow);
	sphere(ray, e, e->sphere3, big_shadow);
	sphere(ray, e, e->sphere4, big_shadow);
	sphere(ray, e, e->sphere5, big_shadow);
	sphere(ray, e, e->sphere6, big_shadow);
	sphere(ray, e, e->sphere7, big_shadow);
	sphere(ray, e, e->sphere8, big_shadow);
}

void		big_balayage(t_env *e)
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
			big_balayage2(e, ray);
			cylindre(ray, e, e->cylindre, big_shadow);
			cylindre(ray, e, e->cylindre2, big_shadow);
			cylindre(ray, e, e->cylindre3, big_shadow);
			cylindre(ray, e, e->cylindre4, big_shadow);
			plan(ray, e, e->plan1, big_shadow);
			plan(ray, e, e->plan2, big_shadow);
			plan(ray, e, e->plan3, big_shadow);
			mlx_pixel_put_to_image(p.x, p.y, e);
			e->color = 0;
			e->k = -1;
		}
		p.x = 0;
	}
}
