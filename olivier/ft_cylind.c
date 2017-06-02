/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylind.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <oseng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 18:39:15 by oseng             #+#    #+#             */
/*   Updated: 2016/04/22 12:28:35 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static	void	ft_lux_cyl(t_env *a, t_obj obj)
{
	double		coef;
	t_vect		n;
	t_vect		vectlum;

	coef = 1.0;
	n.x = (a->pt.x - obj.center.x);
	n.y = (a->pt.y - obj.center.y);
	n.z = 0;
	vectlum.x = -(a->pt.x - a->lum[0].x);
	vectlum.y = -(a->pt.y - a->lum[0].y);
	vectlum.z = -(a->pt.z - a->lum[0].z);
	a->cos_lum = coef * (vectlum.x * n.x + vectlum.y * n.y + vectlum.z * n.z) /
	(sqrt(pow(vectlum.x, 2) + pow(vectlum.y, 2) + pow(vectlum.z, 2)) *
	sqrt(pow(n.x, 2) + pow(n.y, 2) + pow(n.z, 2)));
	if (a->cos_lum >= 0.000001)
	{
		ft_ligth(a->cos_lum, obj, a);
	}
	else
		a->color = 0x000000;
}

static int		ft_disc_cyl(t_env *a, t_vect coef, t_vect ray, t_vect cam)
{
	double		discr;
	double		k1;
	double		k2;

	if ((discr = pow(coef.y, 2) - (4 * coef.x * coef.z)) > 0.000001)
	{
		k1 = (-coef.y - sqrt(discr)) / (2 * coef.x);
		k2 = (-coef.y + sqrt(discr)) / (2 * coef.x);
		a->k = (k1 > k2) ? k2 : k1;
		if (a->k > 0.000001)
		{
			if (a->k < a->k0)
			{
				a->k0 = a->k;
				a->pt.x = cam.x + a->k * ray.x;
				a->pt.y = cam.y + a->k * ray.y;
				a->pt.z = cam.z + a->k * ray.z;
				return (1);
			}
		}
	}
	return (0);
}

int				ft_cylind(t_env *a, t_obj cylin)
{
	t_vect		coef;
	t_vect		cam;
	t_vect		ray;

	cam = ft_tmp(a->cam);
	ray = ft_tmp(a->ray);
	cam = ft_rot(cam, cylin);
	ray = ft_rot(ray, cylin);
	cylin.center = ft_rot(cylin.center, cylin);
	coef.x = pow(ray.x, 2) + pow(ray.y, 2);
	coef.y = 2 * (ray.x * (cam.x - cylin.center.x) + ray.y * (cam.y -
		cylin.center.y));
	coef.z = pow(cam.x - cylin.center.x, 2) + pow(cam.y - cylin.center.y, 2) -
		pow(cylin.d, 2);
	if (ft_disc_cyl(a, coef, ray, cam) == 1)
	{
		a->color = RGB(cylin.color.x, cylin.color.y, cylin.color.z);
		ft_lux_cyl(a, cylin);
		return (1);
	}
	return (0);
}
