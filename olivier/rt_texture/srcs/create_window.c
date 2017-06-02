/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 14:30:18 by grass-kw          #+#    #+#             */
/*   Updated: 2016/05/20 12:49:59 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		mlx_setup(t_env *e)
{
	if ((e->mlx = mlx_init()) == NULL)
	{
		ft_putendl("fail to connect with X-server");
		exit(1);
	}
	if ((e->win = mlx_new_window(e->mlx, e->w, e->h, "rt_v1")) == NULL)
	{
		ft_putendl("fail to created window");
		exit(1);
	}
	if ((e->img = mlx_new_image(e->mlx, e->w, e->h)) == NULL)
	{
		ft_putendl("fail to created an image");
		exit(1);
	}
	if ((e->data = mlx_get_data_addr(e->img, &(e->bpp)
		, &(e->line), &(e->endian))) == NULL)
	{
		ft_putendl("fail to obtain information from image");
		exit(1);
	}
}

void	create_window(char *s)
{
	t_env	rt1;

	global_parser(s, &rt1);
	mlx_setup(&rt1);
	if (OPENCL == 1)
		opencl_setup(&rt1.cl, rt1.h, rt1.w);
	mlx_string_put(rt1.mlx, rt1.win, rt1.w / 2, rt1.h / 2, 0xFFFFFF, "LOADING...");
	mlx_mouse_hook(rt1.win, my_mouse_funct, &rt1);
	mlx_hook(rt1.win, 2, (1L << 0), key_press, &rt1);
	mlx_hook(rt1.win, 3, (1L << 1), key_release, &rt1);
	mlx_loop_hook(rt1.mlx, expose, &rt1);
	mlx_loop(rt1.mlx);
}
