/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/20 14:30:36 by svelhinh          #+#    #+#             */
/*   Updated: 2016/05/30 18:13:26 by svelhinh         ###   ########.fr       */
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
	if (!(rt->img = mlx_new_image(rt->mlx, rt->w, rt->h)))
		ft_exit("mlx_new_image() in expose() failed");
	rt->data = mlx_get_data_addr(rt->img, &rt->bpp, &rt->line,
			&rt->endian);
	if (OPENCL == 1)
		ft_opencl(rt);
	else
		render(rt);
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img, 0, 0);
	if (rt->menu >= 1 || rt->rotcam != 0 || rt->effect >= 0)// menu et clic droit
		menu(rt);
	mlx_destroy_image(rt->mlx, rt->img);
	return (0);
}

int		key_press(int keycode, t_env *rt)
{
	if (keycode == MENU)
		rt->menu = (rt->menu != 1) ? 1 : 0;
	if (keycode == SAVE)
		save(rt);
	if (keycode == 7)
	{
		for(int i = 0; i < rt->nbobj; i++)
		{
			if (rt->object[i].name == SPHERE)
				rt->object[i].angle.z += 0.1;
		}
	}
	if (keycode == 6)
	{
		for(int i = 0; i < rt->nbobj; i++)
		{
			if (rt->object[i].name == SPHERE)
				rt->object[i].angle.z -= 0.1;
		}
	}
	if (keycode == LEFT)
		rt->keyleft = 1;
	if (keycode == UP)
		rt->keyup = 1;
	if (keycode == RIGHT)
		rt->keyright = 1;
	if (keycode == DOWN)
		rt->keydown = 1;
	if (keycode == 36)
		create_window("scenes/sphere_plane.rt");
	if (keycode == ESC)
	{
		if (OPENCL == 1)
			cl_free(&rt->cl);
		mlx_destroy_window(rt->mlx, rt->win);
		exit(0);
	}
	return (0);
}

int		key_release(int keycode, t_env *rt)
{
	if (keycode == LEFT)
		rt->keyleft = 0;
	if (keycode == UP)
		rt->keyup = 0;
	if (keycode == RIGHT)
		rt->keyright = 0;
	if (keycode == DOWN)
		rt->keydown = 0;
	return (0);
}
