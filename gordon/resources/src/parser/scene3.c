/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grass-kw <grass-kw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 18:43:52 by grass-kw          #+#    #+#             */
/*   Updated: 2016/04/24 18:57:27 by grass-kw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_v1.h"

void        big_init(t_env *e)
{
	t_obj	spot1;

	e->camera.type = CAMERA;
	e->camera.angle = set_coord(0, 0, 0);
	e->camera.origin = set_coord(-1100, 0, 0);
	spot1 = set_coord(-950, 0, 100);
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

void        big_init6(t_env *e)
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

static void    big_init3(t_env *e)
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
    e->sphere8.center.x = -500;2
    e->sphere8.center.y = -200;
    e->sphere8.center.z = 200;
    e->sphere8.rayon = 60;
    e->sphere8.color.x = 200;
    e->sphere8.color.y = 200;
    big_init4(e);
}

static void    big_init4(t_env *e)
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
