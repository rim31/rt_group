/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grass-kw <grass-kw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/19 16:03:37 by grass-kw          #+#    #+#             */
/*   Updated: 2016/04/22 22:13:54 by grass-kw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_v1.h"

void	draw(t_env *e)
{
	int		i;
	int		j;
	t_color color;
	int		rgb;

	i = 0;
	while (i++ < LENGHT)
	{
		j = 0;
		while (j++ < WIDTH)
		{
			color = raytracer(e, i, j);
			rgb = new_color(color);
			set_pixel(e, rgb, i, j);
		}
	}
}
