/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/20 14:30:36 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/03 12:38:41 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		expose(t_env *rt)
{
	if (rt->keyup == 1)
		rt->zz += SPEED;
	if (rt->keydown == 1)
		rt->zz -= SPEED;
	if (rt->keyleft == 1)
		rt->xx -= SPEED / 4;
	if (rt->keyright == 1)
		rt->xx += SPEED / 4;
	rt->bpp = 32;
	rt->line = rt->w * 4;
	if (!(rt->data = (char *)malloc(sizeof(char) * (rt->w * rt->h * 4))))
		ft_exit("\033[31mmalloc of rt->data in expose() failed\n");
	if (OPENCL == 1)
		ft_opencl(rt);
	else
		render(rt);
	if (!rt->i_gtk)
		gtk(rt);
	return (0);
}

// int		key_press(int keycode, t_env *rt)
// {
// 	if (keycode == MENU)
// 		rt->menu = (rt->menu != 1) ? 1 : 0;
// 	if (keycode == SAVE)
// 		save(rt);
// 	if (keycode == 7)
// 	{
// 		for(int i = 0; i < rt->nbobj; i++)
// 		{
// 			if (rt->object[i].name == SPHERE)
// 				rt->object[i].angle.z += 0.1;
// 		}
// 	}
// 	if (keycode == 6)
// 	{
// 		for(int i = 0; i < rt->nbobj; i++)
// 		{
// 			if (rt->object[i].name == SPHERE)
// 				rt->object[i].angle.z -= 0.1;
// 		}
// 	}
// 	if (keycode == LEFT)
// 		rt->keyleft = 1;
// 	if (keycode == UP)
// 		rt->keyup = 1;
// 	if (keycode == RIGHT)
// 		rt->keyright = 1;
// 	if (keycode == DOWN)
// 		rt->keydown = 1;
// 	if (keycode == 36)
// 		create_window("scenes/sphere_plane.rt");
// 	if (keycode == ESC)
// 	{
// 		if (OPENCL == 1)
// 			cl_free(&rt->cl);
// 		// mlx_destroy_window(rt->mlx, rt->win);
// 		exit(0);
// 	}
// 	return (0);
// }
//
// int		key_release(int keycode, t_env *rt)
// {
// 	if (keycode == LEFT)
// 		rt->keyleft = 0;
// 	if (keycode == UP)
// 		rt->keyup = 0;
// 	if (keycode == RIGHT)
// 		rt->keyright = 0;
// 	if (keycode == DOWN)
// 		rt->keydown = 0;
// 	return (0);
// }
