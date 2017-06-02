/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_scene_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/20 11:50:32 by lnieto-m          #+#    #+#             */
/*   Updated: 2016/04/20 17:36:47 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	big_init5(t_env *e)
{
	e->cylindre.center.z = 0;
	e->cylindre.rayon = 30;
	e->cylindre.rotation.x = 0;
	e->cylindre.rotation.y = 0;
	e->cylindre.rotation.z = 0;
	e->cylindre.color.x = 200;
	e->cylindre.color.y = 200;
	e->cylindre.color.z = 200;
	e->cylindre2.center.x = -500;
	e->cylindre2.center.y = 200;
	e->cylindre2.center.z = 0;
	e->cylindre2.rayon = 30;
	e->cylindre2.rotation.x = 0;
	e->cylindre2.rotation.y = 0;
	e->cylindre2.rotation.z = 0;
	e->cylindre2.color.x = 200;
	e->cylindre2.color.y = 200;
	e->cylindre2.color.z = 200;
	e->cylindre3.center.x = -100;
	e->cylindre3.center.y = -200;
	e->cylindre3.center.z = 0;
	e->cylindre3.rayon = 30;
	e->cylindre3.rotation.x = 0;
	e->cylindre3.rotation.y = 0;
	big_init6(e);
}

static void	big_init4(t_env *e)
{
	e->sphere8.color.z = 200;
	e->plan1.normale.x = 1;
	e->plan1.normale.y = 0;
	e->plan1.normale.z = 0;
	e->plan1.d = -300;
	e->plan1.color.x = 50;
	e->plan1.color.y = 50;
	e->plan1.color.z = 255;
	e->plan2.normale.x = 0;
	e->plan2.normale.y = 0;
	e->plan2.normale.z = -1;
	e->plan2.color.x = 100;
	e->plan2.color.y = 100;
	e->plan2.color.z = 100;
	e->plan2.d = 200;
	e->plan3.normale.x = 0;
	e->plan3.normale.y = 0;
	e->plan3.normale.z = 1;
	e->plan3.color.x = 255;
	e->plan3.color.y = 255;
	e->plan3.color.z = 255;
	e->plan3.d = 200;
	e->cylindre.center.x = -100;
	e->cylindre.center.y = 200;
	big_init5(e);
}

static void	big_init3(t_env *e)
{
	e->sphere5.rayon = 60;
	e->sphere5.color.x = 200;
	e->sphere5.color.y = 200;
	e->sphere5.color.z = 200;
	e->sphere6.center.x = -100;
	e->sphere6.center.y = 200;
	e->sphere6.center.z = 200;
	e->sphere6.rayon = 60;
	e->sphere6.color.x = 200;
	e->sphere6.color.y = 200;
	e->sphere6.color.z = 200;
	e->sphere7.center.x = -100;
	e->sphere7.center.y = -200;
	e->sphere7.center.z = 200;
	e->sphere7.rayon = 60;
	e->sphere7.color.x = 200;
	e->sphere7.color.y = 200;
	e->sphere7.color.z = 200;
	e->sphere8.center.x = -500;
	e->sphere8.center.y = -200;
	e->sphere8.center.z = 200;
	e->sphere8.rayon = 60;
	e->sphere8.color.x = 200;
	e->sphere8.color.y = 200;
	big_init4(e);
}

static void	big_init2(t_env *e)
{
	e->sphere2.center.x = -100;
	e->sphere2.center.y = -200;
	e->sphere2.center.z = -200;
	e->sphere2.rayon = 60;
	e->sphere2.color.x = 200;
	e->sphere2.color.y = 200;
	e->sphere2.color.z = 200;
	e->sphere3.center.x = -100;
	e->sphere3.center.y = 200;
	e->sphere3.center.z = -200;
	e->sphere3.rayon = 60;
	e->sphere3.color.x = 200;
	e->sphere3.color.y = 200;
	e->sphere3.color.z = 200;
	e->sphere4.center.x = -500;
	e->sphere4.center.y = 200;
	e->sphere4.center.z = -200;
	e->sphere4.rayon = 60;
	e->sphere4.color.x = 200;
	e->sphere4.color.y = 200;
	e->sphere4.color.z = 200;
	e->sphere5.center.x = -500;
	e->sphere5.center.y = 200;
	e->sphere5.center.z = 200;
	big_init3(e);
}

void		big_init(t_env *e)
{
	e->k = -1;
	e->rot_cam.x = 0;
	e->rot_cam.y = 0;
	e->rot_cam.z = 0;
	e->eye.x = -1100;
	e->eye.y = 0;
	e->eye.z = 0;
	e->spot1.x = -950;
	e->spot1.y = 0;
	e->spot1.z = 100;
	e->sphere.center.x = -600;
	e->sphere.center.y = 0;
	e->sphere.center.z = -100;
	e->sphere.rayon = 20;
	e->sphere.color.x = 255;
	e->sphere.color.y = 0;
	e->sphere.color.z = 0;
	e->sphere1.center.x = -500;
	e->sphere1.center.y = -200;
	e->sphere1.center.z = -200;
	e->sphere1.rayon = 60;
	e->sphere1.color.x = 200;
	e->sphere1.color.y = 200;
	e->sphere1.color.z = 200;
	big_init2(e);
}
