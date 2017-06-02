/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 17:33:49 by lnieto-m          #+#    #+#             */
/*   Updated: 2016/05/12 15:49:35 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		triangle(t_vector r, t_figure tri, double *t, t_vector eye)
{
	t_vector	ab;
	t_vector	ac;
	double		d;
	double		u;
	double		v;
	double		tmp;

	ab = vecsub(tri.a, tri.b);
    ac = vecsub(tri.a, tri.c);
    if (-1 * ab.z * r.y * ac.x + ab.y * r.z * ac.x + r.x * ab.z * ac.y
		+ r.y * ab.x * ac.z - r.z * ab.x * ac.y - r.x * ab.y * ac.z == 0.00001)
        return (0);
    d = vecsub(tri.a, eye);
    v = (-1 * r.x * ab.y * d.z - r.z * ab.x * d.y + ab.y * r.z * d.x
		+ r.x * ab.z * d.y + r.y * ab.x * d.z - ab.z * r.y * d.x) / sol;
    u = (-1 * r.y * d.x * ac.z + r.y * ac.x * d.z - ac.x * r.z * d.y
		+ d.x * r.z * ac.y - r.x * ac.y * d.z + r.x * d.y * ac.z) / sol;
    tmp = -1 * (-1 * d.x * ab.z * ac.y + d.x * ab.y * ac.z + ab.x * ac.y * d.z
		- ab.x * d.y * ac.z - ac.x * ab.y * d.z + ac.x * ab.z * d.y) / sol;
    if (u > 0 && v > 0 && u + v <= 1 && tmp < *t)
	{
		*t = tmp;
		return (1);
	}
	return (0);
}

int		quad(t_vector r, t_figure tri, double *t, t_vector eye)
{
	t_figure	part1;
	t_figure	part2;
	int			ret;
	int			ret2;

	part1 = tri;
	part2 = tri;
	part2.a = tri.d;
	part2.b = tri.c;
	part2.c = tri.b;
	ret = triangle(r, part1, t, eye);
	ret2 = triangle(r, part2, t, eye);
	if (ret != ret2)
		ret = (ret == 1) ? ret : ret2;
	return (ret);
}
