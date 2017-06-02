/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <oseng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 15:17:41 by oseng             #+#    #+#             */
/*   Updated: 2016/05/16 10:51:15 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void rot_rotcam(int button, int x, int y, t_env *rt)
{
	if (button == 1 && rt->rotcam == 1 && x > 320 && x < 480 && y > 30 && y < 60)
		rt->cam_angle.x -= M_PI/ 180;
	else if (button == 1 && rt->rotcam == 1 && x > 320 && x < 480 && y > 60 && y < 90)
		rt->cam_angle.x += M_PI/ 180;
	if (button == 1 && rt->rotcam == 1 && x > 320 && x < 480 && y > 90 && y < 130)
		rt->cam_angle.y += M_PI/ 180;
	else if (button == 1 && rt->rotcam == 1 && x > 320 && x < 480 && y > 130 && y < 150)
		rt->cam_angle.y -= M_PI/ 180;
	if (button == 1 && rt->rotcam == 1 && x > 320 && x < 480 && y > 150 && y < 180)
		rt->cam_angle.z += M_PI/ 180;
	else if (button == 1 && rt->rotcam == 1 && x > 320 && x < 480 && y > 180 && y < 210)
		rt->cam_angle.z -= M_PI/ 180;
}

int		my_mouse_funct(int button, int x, int y, t_env *rt)
{
	if (button == 2)
		rt->rotcam = (rt->rotcam != 1) ? 1 : 0;
	if (rt->rotcam == 1)
	{
		rot_rotcam(button, x, y, rt);
	}
	if (rt->menu >= 1)
	{
		if (button == 1 && rt->menu == 1 && x < 160 && y < 33)
			rt->menu = 2;
		else if (button == 1 && rt->menu == 2 && x < 160 && y > 33 && y < 66)
			rt->menu = 3;
		else if (button == 1 && rt->menu == 3 && x > 160 && x < 320 && y > 33 && y < 66)
			create_window("scenes/scene3.rt");
		else if (button == 1 && rt->menu == 1 && x > 320 && x < 480 && y < 33)
				rt->rotcam = 1;
		else
		{
			rt->menu = 0;
			rt->rotcam = 0;
		}
	}
	return (0);
}

void menu(t_env *rt)
{
	if (rt->menu == 1 && (rt->textur = mlx_xpm_file_to_image(rt->mlx, "img/menu.xpm",
			&rt->pxlh, &rt->pxlw)))
		mlx_put_image_to_window(rt->mlx, rt->win, rt->textur, 1, 1);
	else if (rt->menu == 2 && (rt->textur = mlx_xpm_file_to_image(rt->mlx, "img/menu_open.xpm",
				&rt->pxlh, &rt->pxlw)))
		mlx_put_image_to_window(rt->mlx, rt->win, rt->textur, 1, 1);
	else if (rt->menu == 3 && (rt->textur = mlx_xpm_file_to_image(rt->mlx, "img/menu_open_scene.xpm",
				&rt->pxlh, &rt->pxlw)))
		mlx_put_image_to_window(rt->mlx, rt->win, rt->textur, 1, 1);
	if (rt->rotcam == 1 && (rt->textur = mlx_xpm_file_to_image(rt->mlx, "img/rotcam.xpm",
			&rt->pxlh, &rt->pxlw)))
		mlx_put_image_to_window(rt->mlx, rt->win, rt->textur, 1, 1);
}
