/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <oseng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 11:09:01 by rims              #+#    #+#             */
/*   Updated: 2016/05/03 15:46:05 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"



void menu(t_env *rt)
{



}

// static void		clic_rotation(int keycode, t_env *e)
// {
// 	if (keycode == 1 && rt->menu == 1)
// 	{
// 		if (e->small == 0)
// 			e->small = 1;
// 		else
// 			e->small = 0;
// 	}
// 	if (keycode == 49)
// 	{
// 		if (e->pas == 0.1)
// 			e->pas = 0.3;
// 		else
// 			e->pas = 0.1;
// 	}
// 	if (keycode == 0)
// 	{
// 		if (e->lvl == 1)
// 			e->lvl = 0;
// 		else
// 			e->lvl = 1;
// 	}
// }

int				my_mouse_funct(int button, int x, int y, t_env *rt)
{
	int			a;
	int			b;

	if (button == 1)
	{
		mlx_string_put(e->mlx, e->win, x, y, 0xff00ff, "pan");
		a = (int)e->width;
		b = (int)e->higth;
		usleep(250);
	}
	return (0);
}
