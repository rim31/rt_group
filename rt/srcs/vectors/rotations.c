/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 10:55:45 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/11 15:04:46 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vector	rotations(t_vector vec, double x, double y, double z)
{
	t_vector	tmp;
	double		sinx;
	double		siny;
	double		sinz;

	if (x || y || z)
	{
		sinx = sin(x);
		siny = sin(y);
		sinz = sin(z);
		x = cos(x);
		y = cos(y);
		z = cos(z);
		tmp.x = vec.x;
		tmp.y = vec.y;
		tmp.z = vec.z;
		vec.x = tmp.x * y * z - tmp.y * y * sinz + tmp.z * siny;
		vec.y = tmp.x * (x * sinz + sinx * siny * z) + tmp.y *
			(x * z - sinx * siny * sinz) - tmp.z * sinx *
			y;
		vec.z = tmp.x * (sinx * sinz - x * siny * z) + tmp.y *
			(sinx * z + x * siny * sinz) + tmp.z * x *
			y;
	}
	return (vec);
}
