/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scene_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <oseng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/20 11:17:26 by oseng             #+#    #+#             */
/*   Updated: 2016/04/25 10:39:01 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_scene_4c(t_env *a)
{
	a->obj[5].name = "cylindre";
	a->obj[5].color.x = 0x0F;
	a->obj[5].color.y = 0xFE;
	a->obj[5].color.z = 0x00;
	a->obj[5].center.x = 0.0;
	a->obj[5].center.y = 30;
	a->obj[5].center.z = 0;
	a->obj[5].angle.x = M_PI / 4;
	a->obj[5].angle.y = 0;
	a->obj[5].angle.z = 0;
	a->obj[5].d = 0;
}

static void	ft_scene_4b(t_env *a)
{
	a->obj[3].name = "cone";
	a->obj[3].color.x = 0xFF;
	a->obj[3].color.y = 0x00;
	a->obj[3].color.z = 0xCC;
	a->obj[3].center.x = 0.0;
	a->obj[3].center.y = 40.0;
	a->obj[3].center.z = 40.0;
	a->obj[3].angle.x = 0;
	a->obj[3].angle.y = 0;
	a->obj[3].angle.z = 0;
	a->obj[3].d = 1;
	a->obj[4].name = "plan";
	a->obj[4].color.x = 0xFF;
	a->obj[4].color.y = 0xAF;
	a->obj[4].color.z = 0xA0;
	a->obj[4].center.x = 1.01;
	a->obj[4].center.y = 0.21;
	a->obj[4].center.z = 0.01;
	a->obj[4].d = -10;
	ft_scene_4c(a);
}

static void	ft_scene_4a(t_env *a)
{
	a->obj[1].name = "sphere";
	a->obj[1].color.x = 255;
	a->obj[1].color.y = 0x00;
	a->obj[1].color.z = 0x00;
	a->obj[1].center.x = 0.0;
	a->obj[1].center.y = -30.0;
	a->obj[1].center.z = 5.0;
	a->obj[1].d = 20;
	a->obj[2].name = "cylindre";
	a->obj[2].color.x = 0x0F;
	a->obj[2].color.y = 0xFE;
	a->obj[2].color.z = 0x00;
	a->obj[2].center.x = -20.0;
	a->obj[2].center.y = 0;
	a->obj[2].center.z = 0;
	a->obj[2].angle.x = -M_PI / 4;
	a->obj[2].angle.y = 0;
	a->obj[2].angle.z = 0;
	a->obj[2].d = 2;
	ft_scene_4b(a);
}

void		ft_scene_4(t_env *a)
{
	a->nblum = 0;
	a->nbobjet = 5;
	a->cam.x = -1000;
	a->cam.y = 0;
	a->cam.z = 50;
	a->angle.x = 0.0;
	a->angle.y = 0.0;
	a->angle.z = 0.0;
	a->lum = (t_vect *)malloc(sizeof(t_vect) * 1);
	a->lum[0].x = -100;
	a->lum[0].y = 100;
	a->lum[0].z = 100;
	a->obj = (t_obj *)malloc(sizeof(t_obj) * a->nbobjet + 1);
	a->obj[0].name = "plan";
	a->obj[0].color.x = 0xFF;
	a->obj[0].color.y = 0xFF;
	a->obj[0].color.z = 0x00;
	a->obj[0].center.x = 0.0;
	a->obj[0].center.y = 0.0;
	a->obj[0].center.z = -1;
	a->obj[0].d = -1;
	ft_scene_4a(a);
}
