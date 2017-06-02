/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 10:54:36 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/12 17:33:24 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		init_all(char *file, t_env *rt)
{
	ft_bzero(rt, sizeof(t_env));
	rt->w = 1280;
	rt->h = 720;
	rt->ambient = 0.3;
	rt->filter_color.r = -1;
	rt->filter_color.g = -1;
	rt->filter_color.b = -1;
	rt->end_h = rt->h;
	count_objects(rt, file);
	count_materials(rt, file);
	init_camera(rt);
	count_light(rt, file);
}
