/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/19 19:35:53 by lnieto-m          #+#    #+#             */
/*   Updated: 2016/04/27 13:30:58 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	cone2(t_env *e, t_vector inter, t_figure cone,
			int (fct)(t_env *, t_vector))
{
	t_vector	n;
	t_vector	lux;
	double		cosi;

	n.x = inter.x - cone.center.x;
	n.y = inter.y - cone.center.y;
	n.z = 0;
	lux.x = e->spot1.x - inter.x;
	lux.y = e->spot1.y - inter.y;
	lux.z = e->spot1.z - inter.z;
	cosi = (lux.x * n.x + lux.y * n.y + lux.z * n.z)
		/ (sqrt(pow(lux.x, 2) + pow(lux.y, 2) + pow(lux.z, 2))
		* sqrt(pow(n.x, 2) + pow(n.y, 2) + pow(n.z, 2)));
	if (fct(e, inter) == 1)
		e->color = 0;
	else if (cosi > 0.4)
		e->color = RGB(cone.color.x, cone.color.y
					, cone.color.z);
	else if (cosi > 0.2)
		e->color = RGB(cone.color.x * 0.4, cone.color.y
					* 0.4, cone.color.z * 0.4);
	else if (cosi > 0)
		e->color = RGB(cone.color.x * 0.2, cone.color.y
					* 0.2, cone.color.z * 0.2);
	else
		e->color = 0;
}

void		cone(t_vector vision, t_env *e, t_figure cone,
			int (fct)(t_env *, t_vector))
{
	t_vector	equ;
	t_vector	eye;
	double		sol;
	t_vector	inter;

	eye = rotation(e->eye, cone.rotation);
	vision = rotation(vision, cone.rotation);
	cone.center = rotation(cone.center, cone.rotation);
	equ.x = pow(vision.x, 2) + pow(vision.y, 2) - pow(vision.z, 2);
	equ.y = 2 * (vision.x * (eye.x - cone.center.x) + vision.y
		* (eye.y - cone.center.y) - vision.z * (eye.z - cone.center.z));
	equ.z = pow(eye.x - cone.center.x, 2) + pow(eye.y - cone.center.y, 2)
		- pow(eye.z - cone.center.z, 2);
	if (solution(e, equ, &sol) == 0)
		return ;
	e->k = sol;
	inter.x = eye.x + sol * vision.x;
	inter.y = eye.y + sol * vision.y;
	inter.z = eye.z + sol * vision.z;
	cone2(e, inter, cone, fct);
}
