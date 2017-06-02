/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/19 19:34:56 by lnieto-m          #+#    #+#             */
/*   Updated: 2016/04/20 16:10:13 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	resolve_plan(t_env *e, t_vector equ, double *solution)
{
	if (equ.x == 0)
		return (0);
	*solution = -1 * (equ.y / equ.x);
	if (*solution < 0)
		return (0);
	if (e->k < *solution && e->k >= 0)
		return (0);
	return (1);
}

static void	plan2(t_vector inter, t_env *e, t_figure plan,
			int (fct)(t_env *, t_vector))
{
	t_vector	lux;
	double		cosi;

	lux.x = -1 * (e->spot1.x - inter.x);
	lux.y = (e->spot1.y - inter.y);
	lux.z = (e->spot1.z - inter.z);
	cosi = (lux.x * plan.normale.x + lux.y * plan.normale.y
			+ lux.z * plan.normale.z) / (sqrt(pow(lux.x, 2)
			+ pow(lux.y, 2) + pow(lux.z, 2)) * sqrt(pow(plan.normale.x, 2)
			+ pow(plan.normale.y, 2) + pow(plan.normale.z, 2)));
	if (cosi > 0)
	{
		if (fct(e, inter) == 1)
			e->color = 0;
		else
			e->color = RGB(plan.color.x * cosi, plan.color.y * cosi,
							plan.color.z * cosi);
	}
	else
		e->color = 0;
}

void		plan(t_vector vision, t_env *e, t_figure plan,
			int (fct)(t_env *, t_vector))
{
	t_vector	equ;
	double		sol;
	t_vector	inter;

	equ.x = (plan.normale.x * vision.x + plan.normale.y * vision.y
			+ plan.normale.z * vision.z);
	equ.y = (e->eye.x * plan.normale.x + e->eye.y * plan.normale.y
			+ e->eye.z * plan.normale.z + plan.d);
	if (resolve_plan(e, equ, &sol) == 0)
		return ;
	e->k = sol;
	inter.x = e->eye.x + sol * vision.x;
	inter.y = e->eye.y + sol * vision.y;
	inter.z = e->eye.z + sol * vision.z;
	plan2(inter, e, plan, fct);
}
