/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_scene_init2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/20 17:35:32 by lnieto-m          #+#    #+#             */
/*   Updated: 2016/04/21 14:49:25 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	init5_3(t_env *e)
{
	e->sphere2.color.z = 0;
	e->sphere3.center.x = -200;
	e->sphere3.center.y = -150;
	e->sphere3.center.z = 200;
	e->sphere3.rayon = 55;
	e->sphere3.color.x = 255;
	e->sphere3.color.y = 0;
	e->sphere3.color.z = 0;
	e->plan1.normale.x = 1;
	e->plan1.normale.y = 0;
	e->plan1.normale.z = 0;
	e->plan1.d = -300;
	e->plan1.color.x = 50;
	e->plan1.color.y = 50;
	e->plan1.color.z = 255;
}

static void	init5_2(t_env *e)
{
	e->plan2.normale.x = 0;
	e->plan2.normale.y = 0;
	e->plan2.normale.z = 1;
	e->plan2.color.x = 255;
	e->plan2.color.y = 255;
	e->plan2.color.z = 255;
	e->plan2.d = 0;
	e->cylindre.center.x = 50;
	e->cylindre.center.y = 150;
	e->cylindre.rayon = 30;
	e->cylindre.rotation.x = 0;
	e->cylindre.rotation.y = 0;
	e->cylindre.rotation.z = 0;
	e->cylindre.color.x = 0;
	e->cylindre.color.y = 255;
	e->cylindre.color.z = 0;
	e->cone.center.x = 0;
	e->cone.center.y = -300;
	e->cone.center.z = 50;
	e->cone.rotation.x = 0;
	e->cone.rotation.y = 0;
	e->cone.rotation.z = 0;
	e->cone.color.x = 255;
	e->cone.color.y = 255;
	e->cone.color.z = 0;
}

void		init5(t_env *e)
{
	e->k = -1;
	e->rot_cam.x = 0;
	e->rot_cam.y = 0;
	e->rot_cam.z = 0;
	e->eye.x = -700;
	e->eye.y = 0;
	e->eye.z = 250;
	e->spot1.x = -2000;
	e->spot1.y = -600;
	e->spot1.z = 200;
	e->sphere1.center.x = -250;
	e->sphere1.center.y = 0;
	e->sphere1.center.z = 50;
	e->sphere1.rayon = 55;
	e->sphere1.color.x = 0;
	e->sphere1.color.y = 255;
	e->sphere1.color.z = 255;
	e->sphere2.center.x = 15;
	e->sphere2.center.y = 0;
	e->sphere2.center.z = 0;
	e->sphere2.rayon = 200;
	e->sphere2.color.x = 255;
	e->sphere2.color.y = 0;
	init5_3(e);
	init5_2(e);
}

void		big_init6(t_env *e)
{
	e->cylindre3.rotation.z = 0;
	e->cylindre3.color.x = 200;
	e->cylindre3.color.y = 200;
	e->cylindre3.color.z = 200;
	e->cylindre4.center.x = -500;
	e->cylindre4.center.y = -200;
	e->cylindre4.center.z = 0;
	e->cylindre4.rayon = 30;
	e->cylindre4.rotation.x = 0;
	e->cylindre4.rotation.y = 0;
	e->cylindre4.rotation.z = 0;
	e->cylindre4.color.x = 200;
	e->cylindre4.color.y = 200;
	e->cylindre4.color.z = 200;
}
