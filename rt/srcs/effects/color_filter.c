/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_filter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 11:24:46 by lnieto-m          #+#    #+#             */
/*   Updated: 2016/06/11 14:31:33 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color		color_filter(t_color color, t_color filter)
{
	t_color		final_color;
	double		grey;

	grey = (color.r + color.g + color.b) / 3;
	final_color.r = (int)(filter.r * grey / 123);
	final_color.g = (int)(filter.g * grey / 123);
	final_color.b = (int)(filter.b * grey / 123);
	final_color.r = (final_color.r > 255) ? 255 : final_color.r;
	final_color.g = (final_color.g > 255) ? 255 : final_color.g;
	final_color.b = (final_color.b > 255) ? 255 : final_color.b;
	return (final_color);
}
