/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scene_6bis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <oseng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/20 11:17:26 by oseng             #+#    #+#             */
/*   Updated: 2016/04/20 17:01:48 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_scene_6bisb(t_env *a)
{
	a->obj[15].name = "cylindre";
	a->obj[15].color.x = 0x0F;
	a->obj[15].color.y = 0xFE;
	a->obj[15].color.z = 0x00;
	a->obj[15].center.x = -500.0;
	a->obj[15].center.y = -200;
	a->obj[15].center.z = 0;
	a->obj[15].angle.x = 0;
	a->obj[15].angle.y = 0;
	a->obj[15].angle.z = 0;
	a->obj[15].d = 30;
}

static void	ft_scene_6bisa(t_env *a)
{
	a->obj[13].name = "cylindre";
	a->obj[13].color.x = 0x0F;
	a->obj[13].color.y = 0xFE;
	a->obj[13].color.z = 0x00;
	a->obj[13].center.x = -500.0;
	a->obj[13].center.y = 200;
	a->obj[13].center.z = 0;
	a->obj[13].angle.x = 0;
	a->obj[13].angle.y = 0;
	a->obj[13].angle.z = 0;
	a->obj[13].d = 30;
	a->obj[14].name = "cylindre";
	a->obj[14].color.x = 0x0F;
	a->obj[14].color.y = 0xFE;
	a->obj[14].color.z = 0x00;
	a->obj[14].center.x = -100.0;
	a->obj[14].center.y = -200;
	a->obj[14].center.z = 0;
	a->obj[14].angle.x = 0;
	a->obj[14].angle.y = 0;
	a->obj[14].angle.z = 0;
	a->obj[14].d = 30;
	ft_scene_6bisb(a);
}

void		ft_scene_6bis(t_env *a)
{
	a->obj[12].name = "cylindre";
	a->obj[12].color.x = 0x0F;
	a->obj[12].color.y = 0xFE;
	a->obj[12].color.z = 0x00;
	a->obj[12].center.x = -100.0;
	a->obj[12].center.y = 200;
	a->obj[12].center.z = 0;
	a->obj[12].angle.x = 0;
	a->obj[12].angle.y = 0;
	a->obj[12].angle.z = 0;
	a->obj[12].d = 30;
	ft_scene_6bisa(a);
}
