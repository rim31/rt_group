/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <oseng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/20 14:30:36 by svelhinh          #+#    #+#             */
/*   Updated: 2016/05/05 17:10:29 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void rot_clic(int button, int x, int y, t_env *rt)
{
	if (button == 1 && rt->clic == 1 && x < 125 && y > 30 && y < 55)
		rt->cam_angle.y -= M_PI/ 180;
	else if (button == 1 && rt->clic == 1 && x < 125 && y > 55 && y < 80)
		rt->cam_angle.y += M_PI/ 180;
	if (button == 1 && rt->clic == 1 && x < 125 && y > 80 && y < 105)
		rt->cam_angle.x += M_PI/ 180;
	else if (button == 1 && rt->clic == 1 && x < 125 && y > 105 && y < 130)
		rt->cam_angle.x -= M_PI/ 180;
	if (button == 1 && rt->clic == 1 && x < 125 && y > 130 && y < 155)
		rt->cam_angle.z += M_PI/ 180;
	else if (button == 1 && rt->clic == 1 && x < 125 && y > 155 && y < 180)
		rt->cam_angle.z -= M_PI/ 180;
}

int		my_mouse_funct(int button, int x, int y, t_env *rt)
{
	int fd;
	t_env new_rt;

	fd = 0;
	if (button == 2)
		rt->clic = (rt->clic != 1) ? 1 : 0;
	if (rt->menu >= 1)
	{
		if (button == 1 && rt->menu == 1 && x < 125 && y < 30)
			rt->menu = 2;
		else if (button == 1 && rt->menu == 2 && x < 125 && y > 30 && y < 56)
			rt->menu = 3;
		else if (button == 1 && rt->menu == 3 && x > 125 && x < 250 && y > 30 && y < 56)
		{
			new_rt.mlx = rt->mlx;
			global_parser("scenes/multi_spot.rt" , &new_rt);
			init_mlx(&new_rt);
		}
		else
			rt->menu--;
		}
	if (rt->clic == 1)
		rot_clic(button, x, y, rt);
	return (0);
}

static void menu(t_env *rt)
{
    t_vector color;

	color.x = 0;
	color.y = 1;
	color.z = 2;
	if (rt->menu == 1 && (rt->textur = mlx_xpm_file_to_image(rt->mlx, "img/menu_effect.xpm",
			&rt->pxlh, &rt->pxlw)))
		mlx_put_image_to_window(rt->mlx, rt->win, rt->textur, 1, 1);
	else if (rt->menu == 2 && (rt->textur = mlx_xpm_file_to_image(rt->mlx, "img/menu_open.xpm",
				&rt->pxlh, &rt->pxlw)))
		mlx_put_image_to_window(rt->mlx, rt->win, rt->textur, 1, 1);
	else if (rt->menu == 3 && (rt->textur = mlx_xpm_file_to_image(rt->mlx, "img/menu_open_scenes.xpm",
				&rt->pxlh, &rt->pxlw)))
		mlx_put_image_to_window(rt->mlx, rt->win, rt->textur, 1, 1);
	if (rt->clic == 1 && (rt->textur = mlx_xpm_file_to_image(rt->mlx, "img/rigth_clic.xpm",
			&rt->pxlh, &rt->pxlw)))
		mlx_put_image_to_window(rt->mlx, rt->win, rt->textur, 1, 1);
}

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
	render(rt);

	mlx_put_image_to_window(rt->mlx, rt->win, rt->img, 0, 0);
	if (rt->menu >= 1 || rt->clic != 0)// menu et clic droit
		menu(rt);

	mlx_destroy_image(rt->mlx, rt->img);
	return (0);
}

int		key_press(int keycode, t_env *rt)
{
	if (keycode == MENU)
		rt->menu = (rt->menu != 1) ? 1 : 0;
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
