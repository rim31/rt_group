/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/10 18:02:42 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/12 18:29:10 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**	c[0] = u
**	c[1] = v
*/

static t_color	texture_mapping_s_el(guchar *buffer, t_figure object,
				t_vector inter)
{
	int			t;
	double		c[2];
	double		scale;
	int			alpha;
	t_vector	n;

	n = vecsub(&inter, &object.center);
	(object.name == ELLIPSOIDE) ? (vecscale(&n, 0.5)) : (0);
	normalize(&n);
	n = rotations(n, object.angle.x, object.angle.y, object.angle.z);
	scale = (object.material.procedural.active) ? (2) :
	(object.material.texture.scale);
	c[0] = 0.5 + atan2(n.z, n.x) / (scale * M_PI);
	c[1] = 0.5 - asin(n.y) / M_PI;
	if (object.material.procedural.active)
		object.color = procedural(object, c[0], c[1]);
	else
	{
		alpha = (object.material.texture.alpha) ? (4) : (3);
		t = (int)(c[0] * object.material.texture.width) * alpha +
(int)(c[1] * object.material.texture.height) * object.material.texture.row;
		object.color = new_color((double)buffer[t] / 255,
			(double)buffer[t + 1] / 255, (double)buffer[t + 2] / 255);
	}
	return (object.color);
}

t_color			textures(guchar *buffer, t_figure object, t_vector inter)
{
	if (object.name == SPHERE || object.name == ELLIPSOIDE)
		object.color = texture_mapping_s_el(buffer, object, inter);
	return (object.color);
}
