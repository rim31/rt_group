/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shadow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <oseng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 18:24:02 by oseng             #+#    #+#             */
/*   Updated: 2016/04/22 11:51:39 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_shadow_pla(t_env *a, t_vect ray, t_obj obj, t_vect pt)
{
	double	k;

	k = -(obj.center.x * pt.x + obj.center.y * pt.y + obj.center.z * pt.z +
	obj.d) / (obj.center.x * ray.x + obj.center.y * ray.y +
	obj.center.z * ray.z);
	if (k > 0.000001)
		a->color = a->color;
}

static void	ft_shadow_sph(t_env *a, t_vect ray, t_obj obj, t_vect pt)
{
	double	aa;
	double	bb;
	double	cc;
	double	k1;
	double	k2;

	aa = pow(ray.x, 2) + pow(ray.y, 2) + pow(ray.z, 2);
	bb = 2 * (ray.x * (pt.x - obj.center.x) + ray.y * (pt.y - obj.center.y) +
		ray.z * (pt.z - obj.center.z));
	cc = pow((pt.x - obj.center.x), 2) + pow((pt.y - obj.center.y), 2) +
		pow((pt.z - obj.center.z), 2) - pow(obj.d, 2);
	if ((pow(bb, 2) - (4 * aa * cc)) > 0.000001)
	{
		k1 = (-bb - sqrt(pow(bb, 2) - (4 * aa * cc))) / (2 * aa);
		k2 = (-bb + sqrt(pow(bb, 2) - (4 * aa * cc))) / (2 * aa);
		a->k = (k1 > k2) ? k2 : k1;
		if (a->k > 0.000001)
		{
			if (a->k < a->k0)
				a->color = 0x000000;
		}
	}
}

/*
**		if (ft_disc(a, coef.x, coef.y, coef.z) == 1)
**		a->color = 0x000000;
*/

static void	ft_shadow_cyl(t_env *a, t_obj obj, t_vect pt)
{
	t_vect	coef;
	t_vect	lu;
	t_vect	kk;

	lu.x = a->lum[0].x - pt.x;
	lu.y = a->lum[0].y - pt.y;
	lu.z = a->lum[0].z - pt.z;
	pt = ft_rot(pt, obj);
	lu = ft_rot(lu, obj);
	obj.center = ft_rot(obj.center, obj);
	coef.x = pow(lu.x, 2) + pow(lu.y, 2);
	coef.y = 2 * (lu.x * (pt.x - obj.center.x) + lu.y * (pt.y - obj.center.y));
	coef.z = pow(pt.x - obj.center.x, 2) + pow(pt.y - obj.center.y, 2)
	- pow(obj.d, 2);
	if ((kk.z = pow(coef.y, 2) - (4 * coef.x * coef.z)) > 0.000001)
	{
		kk.x = (-coef.y - sqrt(kk.z)) / (2 * coef.x);
		kk.y = (-coef.y + sqrt(kk.z)) / (2 * coef.x);
		a->k = (kk.x > kk.y) ? kk.y : kk.x;
		if (a->k > 0.000001)
		{
			if (a->k < a->k0)
				a->color = 0x000000;
		}
	}
}

static void	ft_shadow_cone(t_env *a, t_obj obj, t_vect pt)
{
	t_vect	coef;
	t_vect	lum;

	lum.x = a->lum[0].x - pt.x;
	lum.y = a->lum[0].y - pt.y;
	lum.z = a->lum[0].z - pt.z;
	pt = ft_rot(pt, obj);
	lum = ft_rot(lum, obj);
	obj.center = ft_rot(obj.center, obj);
	coef.x = (pow(lum.y, 2) + pow(lum.x, 2) - pow(lum.z, 2));
	coef.y = 2 * ((pt.y - obj.center.y) * lum.y + (pt.x - obj.center.x) * lum.x
	- (pt.z - obj.center.z) * lum.z);
	coef.z = (pow(pt.y - obj.center.y, 2) + pow(pt.x - obj.center.x, 2) -
	pow(pt.z - obj.center.z, 2));
	if ((a->kk.z = pow(coef.y, 2) - (4 * coef.x * coef.z)) > 0.000001)
	{
		a->kk.x = (-coef.y - sqrt(a->kk.z)) / (2 * coef.x);
		a->kk.y = (-coef.y + sqrt(a->kk.z)) / (2 * coef.x);
		a->k = (a->kk.x > a->kk.y) ? a->kk.y : a->kk.x;
		if (a->k > 0.000001)
		{
			if (a->k < a->k0)
				a->color = 0x000000;
		}
	}
}

void		ft_shadow(t_env *a, t_vect ray, t_vect pt)
{
	int		i;

	ray.x *= -1;
	ray.y *= -1;
	ray.z *= -1;
	i = 0;
	while (i <= a->nbobjet)
	{
		if (ft_strcmp(a->obj[i].name, "plan") == 0)
			ft_shadow_pla(a, ray, a->obj[i], pt);
		else if (ft_strcmp(a->obj[i].name, "sphere") == 0)
			ft_shadow_sph(a, ray, a->obj[i], pt);
		else if (ft_strcmp(a->obj[i].name, "cylindre") == 0)
			ft_shadow_cyl(a, a->obj[i], pt);
		else if (ft_strcmp(a->obj[i].name, "cone") == 0)
			ft_shadow_cone(a, a->obj[i], pt);
		else
			ft_error();
		i++;
	}
}
