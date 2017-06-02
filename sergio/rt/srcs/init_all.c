/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 10:54:36 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/03 16:53:25 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		init_all(char *file, t_env *rt)
{
	rt->bg_color.r = 0;
	rt->bg_color.g = 0;
	rt->bg_color.b = 0;
	rt->w = 1280;
	rt->h = 720;
	rt->xx = 0;
	rt->zz = 0;
	rt->nbobj = 0;
	rt->nblight = 0;
	rt->keyup = 0;
	rt->keydown = 0;
	rt->keyleft = 0;
	rt->keyright = 0;
	rt->max_reflect = 0;
	rt->max_refract = 0;
	rt->menu = 0;
	rt->rotcam = 0;
	rt->effect = 0;
	rt->ambient = 0.3;
	rt->i_gtk = 0;
	rt->filter = 0;
	count_objects(rt, file);
	init_camera(rt);
	count_light(rt, file);
}
