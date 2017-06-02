/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plan.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <oseng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 18:39:15 by oseng             #+#    #+#             */
/*   Updated: 2016/04/20 17:35:52 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**static void		ft_chess(t_env *a, t_obj obj) 	ft_chess(a, plan);
**{
**	if ((int)fabs(a->pt.x - H) % 100 < 50 && (int)fabs(a->pt.y - L) % 100 < 50)
**		a->color = 0xCCCCCC * 1;
**	if ((int)fabs(a->pt.x - H) % 100 > 50 && (int)fabs(a->pt.y - L) % 100 > 50)
**	a->color = obj.color.x * 1;
**}
*/

static	void	ft_lux_pla(t_env *a, t_obj plan)
{
	double		cos_lum;
	double		coef;
	t_vect		n;
	t_vect		vectlum;

	plan.center.x *= 1;
	coef = 1;
	n.x = plan.center.x;
	n.y = plan.center.y;
	n.z = plan.center.z;
	vectlum.x = (a->pt.x - a->lum[0].x);
	vectlum.y = (a->pt.y - a->lum[0].y);
	vectlum.z = (a->pt.z - a->lum[0].z);
	cos_lum = coef * (vectlum.x * n.x + vectlum.y * n.y + vectlum.z * n.z) /
	(sqrt(pow(vectlum.x, 2)
	+ pow(vectlum.y, 2) + pow(vectlum.z, 2)) * sqrt(pow(n.x, 2) + pow(n.y, 2) +
	pow(n.z, 2)));
	if (cos_lum >= 0.000001)
	{
		ft_ligth(cos_lum, plan, a);
		ft_shadow(a, vectlum, a->pt);
	}
	else
		a->color = 0x000000;
}

int				ft_plan(t_env *a, t_obj plan)
{
	ft_calvect(a);
	a->k = -(plan.center.x * a->cam.x + plan.center.y * a->cam.y + plan.center.z
	* a->cam.z + plan.d) / (plan.center.x * a->ray.x + plan.center.y * a->ray.y
	+ plan.center.z * a->ray.z);
	if (a->k > 0.000001)
	{
		if (a->k < a->k0)
		{
			a->k0 = a->k;
			a->pt.x = a->cam.x + a->k * a->ray.x;
			a->pt.y = a->cam.y + a->k * a->ray.y;
			a->pt.z = a->cam.z + a->k * a->ray.z;
			ft_lux_pla(a, plan);
			return (1);
		}
	}
	return (0);
}
