/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grass-kw <grass-kw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 06:24:10 by grass-kw          #+#    #+#             */
/*   Updated: 2016/06/11 14:48:58 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			triangle(t_vector r, t_figure tri, double *t, t_vector eye)
{
	t_vector	ab;
	t_vector	ac;
	t_vector	d;
	double		sol;
	t_vector	equ;

	ab = vecsub(&tri.a, &tri.b);
	ac = vecsub(&tri.a, &tri.c);
	if ((sol = ab.z * r.y * ac.x - ab.y * r.z * ac.x - r.x * ab.z * ac.y
		- r.y * ab.x * ac.z + r.z * ab.x * ac.y + r.x * ab.y * ac.z) == 0.00001)
		return (0);
	d = vecsub(&tri.a, &eye);
	equ.x = -1 * (-1 * r.x * ab.y * d.z - r.z * ab.x * d.y + ab.y * r.z * d.x
		+ r.x * ab.z * d.y + r.y * ab.x * d.z - ab.z * r.y * d.x) / sol;
	equ.y = (-1 * r.y * d.x * ac.z + r.y * ac.x * d.z - ac.x * r.z * d.y
		+ d.x * r.z * ac.y - r.x * ac.y * d.z + r.x * d.y * ac.z) / sol;
	equ.z = -1 * (-1 * d.x * ab.z * ac.y + d.x * ab.y * ac.z + ab.x * ac.y * d.z
		- ab.x * d.y * ac.z - ac.x * ab.y * d.z + ac.x * ab.z * d.y) / sol;
	if (equ.y > 0.00001 && equ.x > 0.00001 && equ.y + equ.x <= 1 && equ.z < *t
		&& equ.z > 0.00001)
	{
		*t = equ.z;
		return (1);
	}
	return (0);
}
