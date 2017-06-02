/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_equ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/13 13:44:18 by lnieto-m          #+#    #+#             */
/*   Updated: 2016/04/20 15:41:05 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			co_shadow(t_vector inter, t_env *e, t_figure cone)
{
	t_vector	equ;
	t_vector	lum;
	double		sol;

	lum.x = e->spot1.x - inter.x;
	lum.y = e->spot1.y - inter.y;
	lum.z = e->spot1.z - inter.z;
	inter = rotation(inter, cone.rotation);
	lum = rotation(lum, cone.rotation);
	cone.center = rotation(cone.center, cone.rotation);
	equ.x = pow(lum.x, 2) + pow(lum.y, 2) - pow(lum.z, 2);
	equ.y = 2 * (lum.x * (inter.x - cone.center.x)
			+ lum.y * (inter.y - cone.center.y)
			- lum.z * (inter.z - cone.center.z));
	equ.z = pow((inter.x - cone.center.x), 2)
			+ pow(inter.y - cone.center.y, 2) - pow(inter.z - cone.center.z, 2);
	return (solution(e, equ, &sol));
}

int			cy_shadow(t_vector inter, t_env *e, t_figure cylindre)
{
	t_vector	equ;
	t_vector	lum;
	double		sol;

	lum.x = e->spot1.x - inter.x;
	lum.y = e->spot1.y - inter.y;
	lum.z = e->spot1.z - inter.z;
	inter = rotation(inter, cylindre.rotation);
	lum = rotation(lum, cylindre.rotation);
	cylindre.center = rotation(cylindre.center, cylindre.rotation);
	equ.x = pow(lum.x, 2) + pow(lum.y, 2);
	equ.y = 2 * (lum.x * (inter.x - cylindre.center.x)
			+ lum.y * (inter.y - cylindre.center.y));
	equ.z = pow((inter.x - cylindre.center.x), 2)
			+ pow(inter.y - cylindre.center.y, 2) - pow(cylindre.rayon, 2);
	return (solution(e, equ, &sol));
}

int			s_shadow(t_vector inter, t_env *e, t_figure sphere)
{
	t_vector	equ;
	t_vector	lum;
	double		sol;

	lum.x = e->spot1.x - inter.x;
	lum.y = e->spot1.y - inter.y;
	lum.z = e->spot1.z - inter.z;
	equ.x = pow(lum.x, 2) + pow(lum.y, 2) + pow(lum.z, 2);
	equ.y = 2 * (lum.x * (inter.x - sphere.center.x) + lum.y
		* (inter.y - sphere.center.y) + lum.z * (inter.z - sphere.center.z));
	equ.z = pow(inter.x - sphere.center.x, 2)
		+ pow(inter.y - sphere.center.y, 2) + pow(inter.z - sphere.center.z, 2)
		- pow(sphere.rayon, 2);
	return (solution(e, equ, &sol));
}
