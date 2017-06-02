/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sphere.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <oseng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 18:39:15 by oseng             #+#    #+#             */
/*   Updated: 2016/04/20 17:33:47 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_vect	ft_inv(t_vect vect)
{
	t_vect		tmp;

	tmp.x = -vect.x;
	tmp.y = -vect.y;
	tmp.z = -vect.z;
	return (tmp);
}

static	void	ft_lux_sph(t_env *a, t_obj obj)
{
	double		cos_lum;
	double		coef;
	t_vect		n;
	t_vect		vectlum;

	obj.center.x *= 1;
	coef = 1;
	n.x = (a->pt.x - obj.center.x);
	n.y = (a->pt.y - obj.center.y);
	n.z = (a->pt.z - obj.center.z);
	vectlum.x = -(a->pt.x - a->lum[0].x);
	vectlum.y = -(a->pt.y - a->lum[0].y);
	vectlum.z = -(a->pt.z - a->lum[0].z);
	cos_lum = coef * (vectlum.x * n.x + vectlum.y * n.y + vectlum.z * n.z) /
	(sqrt(pow(vectlum.x, 2)
	+ pow(vectlum.y, 2) + pow(vectlum.z, 2)) * sqrt(pow(n.x, 2) + pow(n.y, 2) +
	pow(n.z, 2)));
	if (cos_lum >= 0.000001)
	{
		ft_ligth(cos_lum, obj, a);
		ft_shadow(a, ft_inv(vectlum), a->pt);
	}
	else
		a->color = 0x000000;
}

int				ft_sphere(t_env *a, t_obj sphere)
{
	double		aa;
	double		bb;
	double		cc;

	aa = pow(a->ray.x, 2) + pow(a->ray.y, 2) + pow(a->ray.z, 2);
	bb = 2 * (a->ray.x * (a->cam.x - sphere.center.x) + a->ray.y * (a->cam.y -
	sphere.center.y) + a->ray.z * (a->cam.z - sphere.center.z));
	cc = pow(a->cam.x - sphere.center.x, 2) + pow(a->cam.y - sphere.center.y, 2)
	+ pow(a->cam.z - sphere.center.z, 2) - pow(sphere.d, 2);
	if (ft_disc(a, aa, bb, cc) == 1)
	{
		a->color = RGB(sphere.color.x, sphere.color.y, sphere.color.z);
		ft_lux_sph(a, sphere);
		return (1);
	}
	return (0);
}
