/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cone.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <oseng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 18:39:15 by oseng             #+#    #+#             */
/*   Updated: 2016/04/22 12:28:27 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static	void	ft_lux_cone(t_env *a, t_obj obj)
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

static int		ft_disc_cone(t_env *a, t_vect coef, t_vect ray, t_vect cam)
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

int				ft_cone(t_env *a, t_obj cone)
{
	t_vect		coef;
	t_vect		cam;
	t_vect		ray;

	cam = ft_tmp(a->cam);
	ray = ft_tmp(a->ray);
	cam = ft_rot(cam, cone);
	ray = ft_rot(ray, cone);
	cone.center = ft_rot(cone.center, cone);
	coef.x = (pow(ray.y, 2) + pow(ray.x, 2) - pow(ray.z, 2));
	coef.y = 2 * ((cam.y - cone.center.y) * ray.y + (cam.x - cone.center.x) *
		ray.x - (cam.z - cone.center.z) * ray.z);
	coef.z = (pow(cam.y - cone.center.y, 2) + pow(cam.x - cone.center.x, 2) -
		pow(cam.z - cone.center.z, 2));
	if (ft_disc_cone(a, coef, ray, cam) == 1)
	{
		a->color = RGB(cone.color.x, cone.color.y, cone.color.z);
		ft_lux_cone(a, cone);
		return (1);
	}
	return (0);
}
