/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_init2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/20 10:57:01 by lnieto-m          #+#    #+#             */
/*   Updated: 2016/04/27 10:39:26 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		init4(t_env *e)
{
	e->k = -1;
	e->rot_cam.x = 0;
	e->rot_cam.y = 0;
	e->rot_cam.z = 0;
	e->eye.x = -500;
	e->eye.y = 0;
	e->eye.z = 0;
	e->spot1.x = -500;
	e->spot1.y = -300;
	e->spot1.z = 0;
	e->sphere1.center.x = 0;
	e->sphere1.center.y = 0;
	e->sphere1.center.z = 0;
	e->sphere1.rayon = 100;
	e->sphere1.color.x = 255;
	e->sphere1.color.y = 0;
	e->sphere1.color.z = 0;
}

void		init3(t_env *e)
{
	e->k = -1;
	e->rot_cam.x = 0;
	e->rot_cam.y = 0;
	e->rot_cam.z = 0;
	e->eye.x = -500;
	e->eye.y = 0;
	e->eye.z = 0;
	e->spot1.x = -500;
	e->spot1.y = 300;
	e->spot1.z = 0;
	e->cylindre.center.x = 0;
	e->cylindre.center.y = 0;
	e->cylindre.center.z = 0;
	e->cylindre.rayon = 100;
	e->cylindre.rotation.x = 0;
	e->cylindre.rotation.y = 0;
	e->cylindre.rotation.z = 0;
	e->cylindre.color.x = 0;
	e->cylindre.color.y = 0;
	e->cylindre.color.z = 255;
}

void		init2(t_env *e)
{
	e->k = -1;
	e->rot_cam.x = 0;
	e->rot_cam.y = 0;
	e->rot_cam.z = 0;
	e->eye.x = -4000;
	e->eye.y = 0;
	e->eye.z = 100;
	e->spot1.x = -2000;
	e->spot1.y = -200;
	e->spot1.z = 200;
	e->cone.center.x = 0;
	e->cone.center.y = 0;
	e->cone.center.z = 50;
	e->cone.rotation.x = 0;
	e->cone.rotation.y = 0;
	e->cone.rotation.z = 0;
	e->cone.color.x = 255;
	e->cone.color.y = 0;
	e->cone.color.z = 255;
	e->plan1.normale.x = 0;
	e->plan1.normale.y = 0;
	e->plan1.normale.z = 1;
	e->plan1.color.x = 50;
	e->plan1.color.y = 50;
	e->plan1.color.z = 255;
}
