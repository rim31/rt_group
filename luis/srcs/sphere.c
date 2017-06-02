/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/19 19:34:20 by lnieto-m          #+#    #+#             */
/*   Updated: 2016/04/27 13:32:17 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	sphere2(t_env *e, t_vector inter, t_figure sphere,
			int (fct)(t_env *, t_vector))
{
	t_vector	n;
	t_vector	lux;
	double		cosi;

	(void)fct;
	n.x = inter.x - sphere.center.x;
	n.y = inter.y - sphere.center.y;
	n.z = inter.z - sphere.center.z;
	lux.x = e->spot1.x - inter.x;
	lux.y = e->spot1.y - inter.y;
	lux.z = e->spot1.z - inter.z;
	cosi = (lux.x * n.x + lux.y * n.y + lux.z * n.z)
		/ (sqrt(pow(lux.x, 2) + pow(lux.y, 2) + pow(lux.z, 2))
		* sqrt(pow(n.x, 2) + pow(n.y, 2) + pow(n.z, 2)));
	if (fct(e, inter) == 1)
		e->color = 0;
	else if (cosi > 0.4)
		e->color = RGB(sphere.color.x, sphere.color.y
					, sphere.color.z);
	else if (cosi > 0.2)
		e->color = RGB(sphere.color.x * 0.4, sphere.color.y
					* 0.4, sphere.color.z * 0.4);
	else if (cosi > 0)
		e->color = RGB(sphere.color.x * 0.2, sphere.color.y
					* 0.2, sphere.color.z * 0.2);
	else
		e->color = 0;
}

void		sphere(t_vector vision, t_env *e, t_figure sphere,
			int (fct)(t_env *, t_vector))
{
	t_vector	equ;
	double		sol;
	t_vector	inter;

	equ.x = pow(vision.x, 2) + pow(vision.y, 2) + pow(vision.z, 2);
	equ.y = 2 * (vision.x * (e->eye.x - sphere.center.x)
		+ vision.y * (e->eye.y - sphere.center.y)
		+ vision.z * (e->eye.z - sphere.center.z));
	equ.z = pow(e->eye.x - sphere.center.x, 2)
		+ pow(e->eye.y - sphere.center.y, 2)
		+ pow(e->eye.z - sphere.center.z, 2) - pow(sphere.rayon, 2);
	if (solution(e, equ, &sol) == 0)
		return ;
	e->k = sol;
	inter.x = e->eye.x + sol * vision.x;
	inter.y = e->eye.y + sol * vision.y;
	inter.z = e->eye.z + sol * vision.z;
	sphere2(e, inter, sphere, fct);
}
