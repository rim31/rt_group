/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grass-kw <grass-kw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/19 15:30:03 by grass-kw          #+#    #+#             */
/*   Updated: 2016/04/21 06:59:07 by grass-kw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_v1.h"

static void	rotation_x(t_coor *a, double angle)
{
	double tmp_x;
	double tmp_y;
	double tmp_z;

	if (angle != ZERO)
	{
		tmp_x = a->x;
		tmp_y = (cos(angle) * a->y) + (-sin(angle) * a->z);
		tmp_z = (sin(angle) * a->y) + (cos(angle) * a->z);
		a->x = tmp_x;
		a->y = tmp_y;
		a->z = tmp_z;
	}
}

static void	rotation_y(t_coor *a, double angle)
{
	double tmp_x;
	double tmp_y;
	double tmp_z;

	if (angle != ZERO)
	{
		tmp_x = (cos(angle) * a->x) + (sin(angle) * a->z);
		tmp_y = a->y;
		tmp_z = (-sin(angle) * a->x) + (cos(angle) * a->z);
		a->x = tmp_x;
		a->y = tmp_y;
		a->z = tmp_z;
	}
}

static void	rotation_z(t_coor *a, double angle)
{
	double tmp_x;
	double tmp_y;
	double tmp_z;

	if (angle != ZERO)
	{
		tmp_x = cos(angle) * a->x - sin(angle) * a->y;
		tmp_y = sin(angle) * a->x + cos(angle) * a->y;
		tmp_z = a->z;
		a->x = tmp_x;
		a->y = tmp_y;
		a->z = tmp_z;
	}
}

void	rotation_inverse(t_coor *a, t_coor angle)
{
	rotation_x(a, (-1) * angle.x);
	rotation_y(a, (-1) * angle.y);
	rotation_z(a, (-1) * angle.z);
}

void	rotation(t_coor *a, t_coor angle)
{
	rotation_x(a, angle.x);
	rotation_y(a, angle.y);
	rotation_z(a, angle.z);
}
