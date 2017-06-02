/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grass-kw <grass-kw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/11 10:10:59 by grass-kw          #+#    #+#             */
/*   Updated: 2016/04/11 10:13:11 by grass-kw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_v1.h"

void	set_pixel(t_env *e, int color, int x, int y)
{
	unsigned int	color2;

	color2 = mlx_get_color_value(e->mlx, color);
	if ((x < LENGHT && x >= 0) && (y < WIDTH && y >= 0))
		ft_memcpy(&e->data[(x * 4) + (y * e->size_line)],
			&color2, (size_t)sizeof(int));
}
