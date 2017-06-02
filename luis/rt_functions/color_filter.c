/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_filter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 10:28:57 by lnieto-m          #+#    #+#             */
/*   Updated: 2016/04/29 10:23:23 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		grey_filter(t_color color)
{
	int	grey;

	grey = (color.r + color.g + color.b) / 3;
	return (grey * 0x10000 + grey * 0x100 + grey);
}

static int		sepia_filter(t_color color, t_color filter)
{
	t_color		sepia;
	double		grey;

	grey = (color.r + color.g + color.b) / 3;
	sepia.r = (int)(filter.r * grey / 123);
	sepia.g = (int)(filter.g * grey / 123);
	sepia.b = (int)(filter.b * grey / 123);
	sepia.r = (sepia.r > 255) ? 255 : sepia.r;
	sepia.g = (sepia.g > 255) ? 255 : sepia.g;
	sepia.b = (sepia.b > 255) ? 255 : sepia.b;
	return (sepia.r * 0x10000 + sepia.g * 0x100 + sepia.b);
}
