/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grass-kw <grass-kw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 17:09:47 by grass-kw          #+#    #+#             */
/*   Updated: 2016/04/24 18:59:05 by grass-kw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_v1.h"

void	valid_rgb(t_color *color)
{
	color->r = (color->r > 255) ? 255 : color->r;
	color->r = (color->r < 0) ? 0 : color->r;
	color->g = (color->g > 255) ? 255 : color->g;
	color->g = (color->g < 0) ? 0 : color->g;
	color->b = (color->b > 255) ? 255 : color->b;
	color->b = (color->b < 0) ? 0 : color->b;
}
