/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procedural.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/10 18:07:19 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/12 18:12:54 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_color		procedural_bricks(double u, double v, t_figure object)
{
	int	tu;
	int	tv;
	int	odd;
	int	edge;

	tu = (int)(10 * u);
	tv = (int)(10 * v);
	odd = (tu & 0x01) == (tv & 0x01);
	edge = ((10 * u - tu < object.material.procedural.scale) && odd) ||
	(10 * v - tv < object.material.procedural.scale);
	if (edge)
		object.color = new_color(object.material.procedural.color1.r,
			object.material.procedural.color1.g,
			object.material.procedural.color1.b);
	else
		object.color = new_color(object.material.procedural.color2.r,
			object.material.procedural.color2.g,
			object.material.procedural.color2.b);
	return (object.color);
}

static t_color		procedural_random(t_figure object)
{
	double		color;

	color = (double)rand() / (double)RAND_MAX;
	object.color = new_color(color, color, color);
	return (object.color);
}

t_color				procedural(t_figure object, double u,
	double v)
{
	if (object.material.procedural.active == BRICKS)
		object.color = procedural_bricks(u, v, object);
	if (object.material.procedural.active == RANDOM)
		object.color = procedural_random(object);
	return (object.color);
}
