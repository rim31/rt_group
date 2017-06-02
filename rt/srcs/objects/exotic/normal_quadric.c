/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_quadric.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/11 17:41:24 by lnieto-m          #+#    #+#             */
/*   Updated: 2016/06/12 10:46:28 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vector			normale_parab(t_vector i)
{
	t_vector n;

	n.x = 2 * i.x;
	n.y = -2 * i.y;
	n.z = 2 * i.z;
	return (n);
}

t_vector			normal_torus(t_vector i, t_figure to)
{
	t_vector	n;
	double		c;

	i = rotations(i, to.angle.x, to.angle.y, to.angle.z);
	c = ((i.x - to.center.x) * (i.x - to.center.x) + (i.y - to.center.y) * (i.y
		- to.center.y) + (i.z - to.center.z) * (i.z - to.center.z)
		- to.separation * to.separation - to.radius * to.radius);
	n.x = 4 * c * (i.x - to.center.x);
	n.y = 4 * (i.y - to.center.y) * (c + 2 * to.separation * to.separation);
	n.z = 4 * c * (i.z - to.center.z);
	return (n);
}
