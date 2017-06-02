/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scene_6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <oseng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/20 11:17:26 by oseng             #+#    #+#             */
/*   Updated: 2016/04/22 11:18:55 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_scene_6d(t_env *a)
{
	a->obj[10].name = "sphere";
	a->obj[10].color.x = 255;
	a->obj[10].color.y = 0x00;
	a->obj[10].color.z = 0x00;
	a->obj[10].center.x = -100.0;
	a->obj[10].center.y = -200.0;
	a->obj[10].center.z = 200.0;
	a->obj[10].d = 60;
	a->obj[11].name = "sphere";
	a->obj[11].color.x = 255;
	a->obj[11].color.y = 0x00;
	a->obj[11].color.z = 0x00;
	a->obj[11].center.x = -500.0;
	a->obj[11].center.y = -200.0;
	a->obj[11].center.z = 200.0;
	a->obj[11].d = 60;
	ft_scene_6bis(a);
}

static void	ft_scene_6c(t_env *a)
{
	a->obj[7].name = "sphere";
	a->obj[7].color.x = 255;
	a->obj[7].color.y = 0x00;
	a->obj[7].color.z = 0x00;
	a->obj[7].center.x = -500.0;
	a->obj[7].center.y = 200.0;
	a->obj[7].center.z = -200.0;
	a->obj[7].d = 60;
	a->obj[8].name = "sphere";
	a->obj[8].color.x = 255;
	a->obj[8].color.y = 0x00;
	a->obj[8].color.z = 0x00;
	a->obj[8].center.x = -500.0;
	a->obj[8].center.y = 200.0;
	a->obj[8].center.z = 200.0;
	a->obj[8].d = 60;
	a->obj[9].name = "sphere";
	a->obj[9].color.x = 255;
	a->obj[9].color.y = 0x00;
	a->obj[9].color.z = 0x00;
	a->obj[9].center.x = -100.0;
	a->obj[9].center.y = 200.0;
	a->obj[9].center.z = 200.0;
	a->obj[9].d = 60;
	ft_scene_6d(a);
}

static void	ft_scene_6b(t_env *a)
{
	a->obj[4].name = "sphere";
	a->obj[4].color.x = 255;
	a->obj[4].color.y = 0x00;
	a->obj[4].color.z = 0x00;
	a->obj[4].center.x = -500.0;
	a->obj[4].center.y = -200.0;
	a->obj[4].center.z = -200.0;
	a->obj[4].d = 60;
	a->obj[5].name = "sphere";
	a->obj[5].color.x = 255;
	a->obj[5].color.y = 0x00;
	a->obj[5].color.z = 0x00;
	a->obj[5].center.x = -100.0;
	a->obj[5].center.y = -200.0;
	a->obj[5].center.z = -200.0;
	a->obj[5].d = 60;
	a->obj[6].name = "sphere";
	a->obj[6].color.x = 255;
	a->obj[6].color.y = 0x00;
	a->obj[6].color.z = 0x00;
	a->obj[6].center.x = -100.0;
	a->obj[6].center.y = 200.0;
	a->obj[6].center.z = -200.0;
	a->obj[6].d = 60;
	ft_scene_6c(a);
}

static void	ft_scene_6a(t_env *a)
{
	a->obj[1].name = "plan";
	a->obj[1].color.x = 0xFF;
	a->obj[1].color.y = 0xFF;
	a->obj[1].color.z = 0xCC;
	a->obj[1].center.x = 1.0;
	a->obj[1].center.y = 0.0;
	a->obj[1].center.z = 0.0;
	a->obj[1].d = -300;
	a->obj[2].name = "plan";
	a->obj[2].color.x = 0xFF;
	a->obj[2].color.y = 0xFF;
	a->obj[2].color.z = 0xCC;
	a->obj[2].center.x = 0.0;
	a->obj[2].center.y = 0.0;
	a->obj[2].center.z = 1.0;
	a->obj[2].d = -200;
	a->obj[3].name = "sphere";
	a->obj[3].color.x = 255;
	a->obj[3].color.y = 0x00;
	a->obj[3].color.z = 0x00;
	a->obj[3].center.x = -600.0;
	a->obj[3].center.y = 0.0;
	a->obj[3].center.z = 20.0;
	a->obj[3].d = 20;
	ft_scene_6b(a);
}

void		ft_scene_6(t_env *a)
{
	a->nblum = 0;
	a->nbobjet = 15;
	a->cam.x = -1100;
	a->cam.y = 0;
	a->cam.z = 0;
	a->angle.x = 0.0;
	a->angle.y = 0.0;
	a->angle.z = 0.0;
	a->lum = (t_vect *)malloc(sizeof(t_vect));
	a->lum[0].x = -1000;
	a->lum[0].y = 0;
	a->lum[0].z = 100;
	a->obj = (t_obj *)malloc(sizeof(t_obj) * a->nbobjet + 2);
	a->obj[0].name = "plan";
	a->obj[0].color.x = 0xFF;
	a->obj[0].color.y = 0xFF;
	a->obj[0].color.z = 0xCC;
	a->obj[0].center.x = 0.0;
	a->obj[0].center.y = 0.0;
	a->obj[0].center.z = -1;
	a->obj[0].d = -200;
	ft_scene_6a(a);
}
