/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scene_7.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <oseng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/20 11:17:26 by oseng             #+#    #+#             */
/*   Updated: 2016/04/22 12:27:17 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_scene_7a(t_env *a)
{
	a->obj[0].center.y = 0.0;
	a->obj[0].center.z = -1;
	a->obj[0].d = -1;
	a->obj[1].name = "sphere";
	a->obj[1].color.x = 0xCC;
	a->obj[1].color.y = 0x00;
	a->obj[1].color.z = 0x00;
	a->obj[1].center.x = -50.0;
	a->obj[1].center.y = 0.0;
	a->obj[1].center.z = 50.0;
	a->obj[1].d = 20;
	a->obj[2].name = "plan";
	a->obj[2].color.x = 0xFF;
	a->obj[2].color.y = 0xFF;
	a->obj[2].color.z = 0x00;
	a->obj[2].center.x = -1.01;
	a->obj[2].center.y = 0.21;
	a->obj[2].center.z = 0.01;
	a->obj[2].d = -10;
}

void		ft_scene_7(t_env *a)
{
	a->nbobjet = 2;
	a->nblum = 2;
	a->cam.x = -300;
	a->cam.y = 0;
	a->cam.z = 50;
	a->angle.x = 0.0;
	a->angle.y = 0.0;
	a->angle.z = 0.0;
	a->lum = (t_vect *)malloc(sizeof(t_vect) * a->nblum + 1);
	a->lum[0].x = -100;
	a->lum[0].y = 100;
	a->lum[0].z = 10;
	a->lum[1].x = -100;
	a->lum[1].y = 0;
	a->lum[1].z = 10;
	a->lum[2].x = -100;
	a->lum[2].y = -100;
	a->lum[2].z = 10;
	a->obj = (t_obj *)malloc(sizeof(t_obj) * a->nbobjet + 1);
	a->obj[0].name = "plan";
	a->obj[0].color.x = 0xFF;
	a->obj[0].color.y = 0xFF;
	a->obj[0].color.z = 0x00;
	a->obj[0].center.x = 0.0;
	ft_scene_7a(a);
}
