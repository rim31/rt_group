/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calcul.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 18:24:02 by oseng             #+#    #+#             */
/*   Updated: 2016/04/28 14:17:13 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vect				ft_norm(t_vect vect)
{
	t_vect	tmp;
	double	tmp1;

	tmp.x = vect.x;
	tmp.y = vect.y;
	tmp.z = vect.z;
	tmp1 = sqrt(pow(tmp.x, 2) + pow(tmp.y, 2) + pow(tmp.z, 2));
	tmp.x = tmp.x / tmp1;
	tmp.y = tmp.y / tmp1;
	tmp.z = tmp.z / tmp1;
	return (tmp);
}

int					ft_disc(t_env *a, double aa, double bb, double cc)
{
	double	discr;
	double	k1;
	double	k2;

	if ((discr = pow(bb, 2) - (4 * aa * cc)) > 0.000001)
	{
		k1 = (-bb - sqrt(discr)) / (2 * aa);
		k2 = (-bb + sqrt(discr)) / (2 * aa);
		a->k = (k1 > k2) ? k2 : k1;
		if (a->k > 0.000001)
		{
			if (a->k < a->k0)
			{
				a->k0 = a->k;
				a->pt.x = a->cam.x + a->k0 * a->ray.x;
				a->pt.y = a->cam.y + a->k0 * a->ray.y;
				a->pt.z = a->cam.z + a->k0 * a->ray.z;
				return (1);
			}
		}
	}
	return (0);
}

t_vect				ft_rot(t_vect vect, t_obj objet)
{
	double			tmp1;
	double			tmp2;

	tmp1 = vect.y;
	tmp2 = vect.z;
	vect.y = tmp1 * cos(objet.angle.x) - tmp2 * sin(objet.angle.x);
	vect.z = tmp1 * sin(objet.angle.x) + tmp2 * cos(objet.angle.x);
	tmp1 = vect.x;
	tmp2 = vect.z;
	vect.x = tmp1 * cos(objet.angle.y) + tmp2 * sin(objet.angle.y);
	vect.z = -tmp1 * sin(objet.angle.y) + tmp2 * cos(objet.angle.y);
	tmp1 = vect.x;
	tmp2 = vect.y;
	vect.x = tmp1 * cos(objet.angle.z) - tmp2 * sin(objet.angle.z);
	vect.y = tmp1 * sin(objet.angle.z) + tmp2 * cos(objet.angle.z);
	return (vect);
}

t_vect				ft_rot_inv(t_vect vect, t_obj objet)
{
	double			tmp1;
	double			tmp2;
	t_vect			angle;

	angle.x = -objet.angle.x;
	angle.y = -objet.angle.y;
	angle.z = -objet.angle.z;
	tmp1 = vect.y;
	tmp2 = vect.z;
	vect.y = tmp1 * cos(angle.x) - tmp2 * sin(angle.x);
	vect.z = tmp1 * sin(angle.x) + tmp2 * cos(angle.x);
	tmp1 = vect.x;
	tmp2 = vect.z;
	vect.x = tmp1 * cos(angle.y) + tmp2 * sin(angle.y);
	vect.z = -tmp1 * sin(angle.y) + tmp2 * cos(angle.y);
	tmp1 = vect.x;
	tmp2 = vect.y;
	vect.x = tmp1 * cos(angle.z) - tmp2 * sin(angle.z);
	vect.y = tmp1 * sin(angle.z) + tmp2 * cos(angle.z);
	return (vect);
}

int					ft_ligth(double cos_lum, t_obj obj, t_env *a)
{
	unsigned char	b;
	unsigned char	g;
	unsigned char	r;

	r = obj.color.x;
	r = (r * cos_lum > 0xFF) ? 0xFF : r * cos_lum;
	g = obj.color.y;
	g = (g * cos_lum > 0xFF) ? 0xFF : g * cos_lum;
	b = obj.color.z;
	b = (b * cos_lum > 0xFF) ? 0xFF : b * cos_lum;
	a->color = RGB(r, g, b);
	return (a->color);
}
