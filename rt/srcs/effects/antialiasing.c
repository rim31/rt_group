/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 09:38:41 by lnieto-m          #+#    #+#             */
/*   Updated: 2016/06/11 14:25:14 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				free_aliasing_tab(t_color **aliasing_tab, t_env *rt,
					int aliasing)
{
	int			i;

	i = 0;
	while (i < (int)(rt->end_h - rt->start_h + 1) * sqrt(aliasing))
		free(aliasing_tab[i++]);
	free(aliasing_tab);
}

static t_color		average_color_16(t_color **tab, int x, int y)
{
	t_color		a;

	a.r = (tab[y][x].r + tab[y][x + 1].r + tab[y][x + 2].r + tab[y][x + 3].r
		+ tab[y + 1][x].r + tab[y + 1][x + 1].r + tab[y + 1][x + 2].r +
		tab[y + 1][x + 3].r + tab[y + 2][x].r + tab[y + 2][x + 1].r
		+ tab[y + 2][x + 2].r + tab[y + 2][x + 3].r + tab[y + 3][x].r
		+ tab[y + 3][x + 1].r + tab[y + 3][x + 2].r +
		tab[y + 3][x + 3].r) / 16;
	a.g = (tab[y][x].g + tab[y][x + 1].g + tab[y][x + 2].g + tab[y][x + 3].g
		+ tab[y + 1][x].g + tab[y + 1][x + 1].g + tab[y + 1][x + 2].g +
		tab[y + 1][x + 3].g + tab[y + 2][x].g + tab[y + 2][x + 1].g
		+ tab[y + 2][x + 2].g + tab[y + 2][x + 3].g + tab[y + 3][x].g
		+ tab[y + 3][x + 1].g + tab[y + 3][x + 2].g +
		tab[y + 3][x + 3].g) / 16;
	a.b = (tab[y][x].b + tab[y][x + 1].b + tab[y][x + 2].b + tab[y][x + 3].b
		+ tab[y + 1][x].b + tab[y + 1][x + 1].b + tab[y + 1][x + 2].b +
		tab[y + 1][x + 3].b + tab[y + 2][x].b + tab[y + 2][x + 1].b
		+ tab[y + 2][x + 2].b + tab[y + 2][x + 3].b + tab[y + 3][x].b
		+ tab[y + 3][x + 1].b + tab[y + 3][x + 2].b
		+ tab[y + 3][x + 3].b) / 16;
	return (a);
}

static int			average_color(t_color **tab, int x, int y, t_env *rt)
{
	t_color		a;
	int			lim_x;
	int			lim_y;

	a.r = tab[y][x].r;
	a.g = tab[y][x].g;
	a.b = tab[y][x].b;
	lim_x = rt->w * sqrt(rt->antialiasing);
	lim_y = (int)(rt->end_h - rt->start_h + 1) * sqrt(rt->antialiasing);
	if (rt->antialiasing == 4 && y + 1 < lim_y && x + 1 < lim_x)
	{
		a.r = (tab[y][x].r + tab[y][x + 1].r + tab[y + 1][x].r
			+ tab[y + 1][x + 1].r) / 4;
		a.g = (tab[y][x].g + tab[y][x + 1].g + tab[y + 1][x].g
			+ tab[y + 1][x + 1].g) / 4;
		a.b = (tab[y][x].b + tab[y][x + 1].b + tab[y + 1][x].b
			+ tab[y + 1][x + 1].b) / 4;
	}
	else if (rt->antialiasing == 16 && y + 3 < lim_y && x + 3 < lim_x)
		a = average_color_16(tab, x, y);
	return ((int)a.r * 0x10000 + (int)a.g * 0x100 + (int)a.b);
}

void				aliasing_render(t_color **aliasing_tab, t_env *rt, double y)
{
	int			x;
	int			x_aliasing;
	int			y_aliasing;
	double		anti_sqrt;

	anti_sqrt = sqrt(rt->antialiasing);
	y_aliasing = 0;
	while (y < (int)rt->end_h)
	{
		x = 0;
		x_aliasing = 0;
		while (x < rt->w)
		{
			mlx_pixel_put_to_image(average_color(aliasing_tab, x_aliasing,
				y_aliasing, rt), rt, x, y);
			x++;
			x_aliasing += anti_sqrt;
		}
		y++;
		y_aliasing += anti_sqrt;
	}
}

t_color				**create_aliasing_tab(t_env *rt, int aliasing)
{
	t_color		**tab;
	int			i;

	i = 0;
	if (!(tab = (t_color **)malloc(sizeof(t_color *) * (int)(rt->end_h
		- rt->start_h + 1) * sqrt(aliasing))))
		return (NULL);
	while (i < (int)(rt->end_h - rt->start_h + 1) * sqrt(aliasing))
	{
		if (!(tab[i] = (t_color *)malloc(sizeof(t_color) * rt->w *
		sqrt(aliasing))))
			return (NULL);
		i++;
	}
	return (tab);
}
