/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expose_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/05 15:08:02 by lnieto-m          #+#    #+#             */
/*   Updated: 2016/04/20 17:52:14 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	scene3(t_env *e, int scn)
{
	if (scn == 6)
	{
		big_init(e);
		big_balayage(e);
	}
	else
	{
		init5(e);
		balayage5(e);
	}
}

static void	scene2(t_env *e, int scn)
{
	if (scn == 3)
	{
		init2(e);
		balayage2(e);
	}
	else if (scn == 4)
	{
		init3(e);
		balayage3(e);
	}
	else
	{
		init4(e);
		balayage4(e);
	}
}

static void	scene1(t_env *e, int scn)
{
	if (scn == 1)
		init0(e);
	else
		init1(e);
	balayage1(e);
}

int			expose_hook(t_env *e)
{
	int		scn;

	e->plan2.d = 0;
	e->plan1.d = 0;
	scn = ft_atoi(e->av);
	if (scn == 1 || scn == 2)
		scene1(e, scn);
	else if (scn == 3 || scn == 4 || scn == 5)
		scene2(e, scn);
	else if (scn == 6 || scn == 7)
		scene3(e, scn);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	return (0);
}
