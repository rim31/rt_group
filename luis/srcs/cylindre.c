/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylindre.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/19 19:35:32 by lnieto-m          #+#    #+#             */
/*   Updated: 2016/04/27 13:32:50 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	cylindre2(t_env *e, t_vector inter, t_figure cylindre,
			int (fct)(t_env *, t_vector))
{
	t_vector	n;
	t_vector	lux;
	double		cosi;

	(void)fct;
	n.x = inter.x - cylindre.center.x;
	n.y = inter.y - cylindre.center.y;
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
		e->color = RGB(cylindre.color.x, cylindre.color.y
					, cylindre.color.z);
	else if (cosi > 0.2)
		e->color = RGB(cylindre.color.x * 0.4, cylindre.color.y
					* 0.4, cylindre.color.z * 0.4);
	else if (cosi > 0)
		e->color = RGB(cylindre.color.x * 0.2, cylindre.color.y
					* 0.2, cylindre.color.z * 0.2);
	else
		e->color = 0;
}

void		cylindre(t_vector vision, t_env *e, t_figure cylindre,
			int (fct)(t_env *, t_vector))
{
	t_vector	equ;
	double		sol;
	t_vector	inter;
	t_vector	eye;

	eye = rotation(e->eye, cylindre.rotation);
	vision = rotation(vision, cylindre.rotation);
	cylindre.center = rotation(cylindre.center, cylindre.rotation);
	equ.x = pow(vision.x, 2) + pow(vision.y, 2);
	equ.y = 2 * (vision.x * (eye.x - cylindre.center.x)
		+ vision.y * (eye.y - cylindre.center.y));
	equ.z = pow((eye.x - cylindre.center.x), 2)
		+ pow(eye.y - cylindre.center.y, 2) - pow(cylindre.rayon, 2);
	if (solution(e, equ, &sol) == 0)
		return ;
	e->k = sol;
	inter.x = eye.x + sol * vision.x;
	inter.y = eye.y + sol * vision.y;
	inter.z = eye.z + sol * vision.z;
	cylindre2(e, inter, cylindre, fct);
}
