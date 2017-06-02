/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scene_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <oseng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/20 11:17:26 by oseng             #+#    #+#             */
/*   Updated: 2016/04/22 09:12:09 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		ft_scene_3(t_env *a)
{
	a->nblum = 0;
	a->nbobjet = 0;
	a->cam.x = -300;
	a->cam.y = 0;
	a->cam.z = 0;
	a->angle.x = 0.0;
	a->angle.y = 0.0;
	a->angle.z = 0.0;
	a->lum = (t_vect *)malloc(sizeof(t_vect));
	a->lum[0].x = -300;
	a->lum[0].y = 30;
	a->lum[0].z = 30;
	a->obj = (t_obj *)malloc(sizeof(t_obj) * 1);
	a->obj[0].name = "cylindre";
	a->obj[0].color.x = 0x00;
	a->obj[0].color.y = 0xFE;
	a->obj[0].color.z = 0x00;
	a->obj[0].center.x = 0.0;
	a->obj[0].center.y = 0;
	a->obj[0].center.z = 0;
	a->obj[0].angle.x = 0;
	a->obj[0].angle.y = 0;
	a->obj[0].angle.z = 0;
	a->obj[0].d = 20;
}
