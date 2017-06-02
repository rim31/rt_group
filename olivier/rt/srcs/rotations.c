/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 10:55:45 by svelhinh          #+#    #+#             */
/*   Updated: 2016/04/27 14:07:39 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vector	rotations(t_vector vec, double x, double y, double z)
{
	double	tmpx;
	double	tmpy;
	double	tmpz;

	tmpx = vec.x;
	tmpy = vec.y;
	tmpz = vec.z;
	vec.x = tmpx * cos(y) * cos(z) - tmpy * cos(y) * sin(z) + tmpz * sin(y);
	vec.y = tmpx * (cos(x) * sin(z) + sin(x) * sin(y) * cos(z)) + tmpy *
		(cos(x) * cos(z) - sin(x) * sin(y) * sin(z)) - tmpz * sin(x) * cos(y);
	vec.z = tmpx * (sin(x) * sin(z) - cos(x) * sin(y) * cos(z)) + tmpy *
		(sin(x) * cos(z) + cos(x) * sin(y) * sin(z)) + tmpz * cos(x) * cos(y);
	return (vec);
}
