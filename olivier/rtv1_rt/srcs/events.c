/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/20 14:30:36 by svelhinh          #+#    #+#             */
/*   Updated: 2016/04/27 15:59:59 by svelhinh         ###   ########.fr       */
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
	raytracer(rt);
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img, 0, 0);
	mlx_destroy_image(rt->mlx, rt->img);
	return (0);
}

int		key_press(int keycode, t_env *rt)
{
	if (keycode == LEFT)
		rt->keyleft = 1;
	if (keycode == UP)
		rt->keyup = 1;
	if (keycode == RIGHT)
		rt->keyright = 1;
	if (keycode == DOWN)
		rt->keydown = 1;
	if (keycode == ESC)
	{
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
