/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_init1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/17 12:27:00 by lnieto-m          #+#    #+#             */
/*   Updated: 2016/04/20 17:11:51 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	init0_2(t_env *e)
{
	e->plan2.normale.x = 0;
	e->plan2.normale.y = 0;
	e->plan2.normale.z = 1;
	e->plan2.color.x = 255;
	e->plan2.color.y = 255;
	e->plan2.color.z = 255;
	e->cylindre.center.x = 0;
	e->cylindre.center.y = 100;
	e->cylindre.rayon = 30;
	e->cylindre.rotation.x = -0.75;
	e->cylindre.rotation.y = 0.1;
	e->cylindre.rotation.z = 0;
	e->cylindre.color.x = 0;
	e->cylindre.color.y = 255;
	e->cylindre.color.z = 0;
	e->cone.center.x = 0;
	e->cone.center.y = -65;
	e->cone.center.z = 50;
	e->cone.rotation.x = 0.55;
	e->cone.rotation.y = 0;
	e->cone.rotation.z = 0;
	e->cone.rayon = 100;
	e->cone.color.x = 255;
	e->cone.color.y = 255;
	e->cone.color.z = 0;
}

void		init0(t_env *e)
{
	e->k = -1;
	e->rot_cam.x = 0;
	e->rot_cam.y = 0;
	e->rot_cam.z = 0;
	e->eye.x = -500;
	e->eye.y = 0;
	e->eye.z = 100;
	e->spot1.x = -2000;
	e->spot1.y = -600;
	e->spot1.z = 200;
	e->sphere1.center.x = -15;
	e->sphere1.center.y = -5;
	e->sphere1.center.z = 45;
	e->sphere1.rayon = 55;
	e->sphere1.color.x = 255;
	e->sphere1.color.y = 0;
	e->sphere1.color.z = 0;
	e->plan1.normale.x = 1;
	e->plan1.normale.y = 0;
	e->plan1.normale.z = 0;
	e->plan1.d = -300;
	e->plan1.color.x = 50;
	e->plan1.color.y = 50;
	e->plan1.color.z = 255;
	init0_2(e);
}

static void	init1_2(t_env *e)
{
	e->plan2.normale.x = 0;
	e->plan2.normale.y = 0;
	e->plan2.normale.z = 1;
	e->plan2.color.x = 255;
	e->plan2.color.y = 255;
	e->plan2.color.z = 255;
	e->plan2.d = 0;
	e->cylindre.center.x = 0;
	e->cylindre.center.y = 100;
	e->cylindre.rayon = 30;
	e->cylindre.rotation.x = -0.75;
	e->cylindre.rotation.y = 0.1;
	e->cylindre.rotation.z = 0;
	e->cylindre.color.x = 0;
	e->cylindre.color.y = 255;
	e->cylindre.color.z = 0;
	e->cone.center.x = 0;
	e->cone.center.y = -65;
	e->cone.center.z = 50;
	e->cone.rotation.x = 0.55;
	e->cone.rotation.y = 0;
	e->cone.rotation.z = 0;
	e->cone.color.x = 255;
	e->cone.color.y = 255;
	e->cone.color.z = 0;
}

void		init1(t_env *e)
{
	e->k = -1;
	e->rot_cam.x = 0;
	e->rot_cam.y = 0.45;
	e->rot_cam.z = 0.7;
	e->eye.x = -200;
	e->eye.y = -300;
	e->eye.z = 250;
	e->spot1.x = -2000;
	e->spot1.y = -600;
	e->spot1.z = 200;
	e->sphere1.center.x = -15;
	e->sphere1.center.y = -5;
	e->sphere1.center.z = 45;
	e->sphere1.rayon = 55;
	e->sphere1.color.x = 255;
	e->sphere1.color.y = 0;
	e->sphere1.color.z = 0;
	e->plan1.normale.x = 1;
	e->plan1.normale.y = 0;
	e->plan1.normale.z = 0;
	e->plan1.d = -300;
	e->plan1.color.x = 50;
	e->plan1.color.y = 50;
	e->plan1.color.z = 255;
	init1_2(e);
}
