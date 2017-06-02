/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limited_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 11:18:35 by svelhinh          #+#    #+#             */
/*   Updated: 2016/05/26 18:13:59 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double	distance(double a, double b, double c)
{
	double	disc;
	double	t0;
	double	t1;
	double	tmp;

	disc = pow(b, 2) - 4 * a * c;
	if (disc < 0)
		return (0);
	t0 = (-b - sqrt(disc)) / (2 * a);
	t1 = (-b + sqrt(disc)) / (2 * a);
	tmp = (t0 < t1) ? (t0) : (t1);
	return (tmp);
}

static int		disk_calcul(t_vector r, t_figure d, double *t, t_vector eye)
{
	double		tmp;
	t_vector	inter;

	tmp = -(0 * eye.x - 1 * eye.y + 0 *
		eye.z + d.radius) / (0 * r.x + - 1 * r.y +
			0 * r.z);
	if (tmp < *t && tmp > 0.00001)
	{
	   inter = calcul_ptinter(eye, r, tmp);
	   if ((inter.x - d.center.x) * (inter.x - d.center.x) +
	   (inter.z - d.center.z) * (inter.z - d.center.z) < pow(d.size, 2))
	   {
		   *t = tmp;
		   return (1);
	   }
	}
	return (0);
}

int				limited_sphere(t_vector r, t_figure s, double *t, t_vector eye, int *disk)
{
	double		a;
	double		b;
	double		c;
	double		tmp;
	t_figure	tmp_1;
	t_vector	inter;

	eye = rotations(eye, s.angle.x, s.angle.y, s.angle.z);
	r = rotations(r, s.angle.x, s.angle.y, s.angle.z);
	s.center = rotations(s.center, s.angle.x, s.angle.y, s.angle.z);
	a = pow(r.x, 2) + pow(r.y, 2) + pow(r.z, 2);
	b = 2 * (r.x * (eye.x - s.center.x) + r.y * (eye.y - s.center.y) + r.z *
		(eye.z - s.center.z));
	c = (pow(eye.x - s.center.x, 2) + pow(eye.y - s.center.y, 2) +
		pow(eye.z - s.center.z, 2)) - pow(s.radius, 2);
	tmp = distance(a, b, c);
	if (tmp < *t && tmp > 0.00001)
	{
		inter = calcul_ptinter(eye, r, tmp);
		tmp_1 = s;
		tmp_1.size = sqrt(s.radius * s.radius - s.separation * s.separation);
		tmp_1.radius = tmp_1.center.y + s.separation;
		if (inter.y <= s.center.y + s.separation)
		{
			*t = tmp;
			*disk = 0;
			return (1);
		}
		if (disk_calcul(r, tmp_1, t, eye))
		{
			*disk = 2;
			return (1);
		}
	}
	return (0);
}

int			limited_cylinder(t_vector r, t_figure cy, double *t, t_vector eye, int *disk)
{
	double		a;
	double		b;
	double		c;
	double		tmp;
	t_figure	tmp_1;
	t_vector	inter;

	eye = rotations(eye, cy.angle.x, cy.angle.y, cy.angle.z);
	r = rotations(r, cy.angle.x, cy.angle.y, cy.angle.z);
	cy.center = rotations(cy.center, cy.angle.x, cy.angle.y, cy.angle.z);
	a = pow(r.x, 2) + pow(r.z, 2);
	b = 2 * (r.x * (eye.x - cy.center.x) + r.z * (eye.z - cy.center.z));
	c = pow(eye.x - cy.center.x, 2) + pow(eye.z - cy.center.z, 2) -
		pow(cy.radius, 2);
	tmp = distance(a, b, c);
	inter = calcul_ptinter(eye, r, tmp);
	tmp_1 = cy;
	tmp_1.size = cy.radius;
	if (tmp < *t && tmp > 0.00001)
	{
		if (inter.y <= cy.center.y + cy.separation && inter.y >= cy.center.y - cy.separation)
		{
			*t = tmp;
			*disk = 0;
			return (1);
		}
		if (inter.y > cy.center.y + cy.separation)
		{
			tmp_1.radius = tmp_1.center.y + cy.separation;
			if (disk_calcul(r, tmp_1, t, eye))
			{
				*disk = 2;
				return (1);
			}
		}
		if (inter.y < cy.center.y - cy.separation)
		{
			tmp_1.radius = tmp_1.center.y - cy.separation;
			if (disk_calcul(r, tmp_1, t, eye))
			{
				*disk = 3;
				return (1);
			}
		}
	}
	return (0);
}

int			limited_cone(t_vector r, t_figure co, double *t, t_vector eye, int *disk)
{
	double		a;
	double		b;
	double		c;
	double		tmp;
	t_figure	tmp_1;
	t_vector	inter;

	eye = rotations(eye, co.angle.x, co.angle.y, co.angle.z);
	r = rotations(r, co.angle.x, co.angle.y, co.angle.z);
	co.center = rotations(co.center, co.angle.x, co.angle.y, co.angle.z);
	a = pow(r.x, 2) - pow(r.y, 2) + pow(r.z, 2);
	b = 2 * (r.x * (eye.x - co.center.x) - r.y * (eye.y - co.center.y) + r.z *
		(eye.z - co.center.z));
	c = (pow(eye.x - co.center.x, 2) - pow(eye.y - co.center.y, 2) +
		pow(eye.z - co.center.z, 2));
	tmp = distance(a, b, c);
	inter = calcul_ptinter(eye, r, tmp);
	tmp_1 = co;
	tmp_1.size = tan(M_PI / 4) * co.separation;
	if (tmp < *t && tmp > 0.00001)
	{
		if (inter.y <= co.center.y + co.separation && inter.y >= co.center.y - co.separation)
		{
			*t = tmp;
			*disk = 0;
			return (1);
		}
		if (inter.y > co.center.y + co.separation)
		{
			tmp_1.radius = tmp_1.center.y + co.separation;
			if (disk_calcul(r, tmp_1, t, eye))
			{
				*disk = 2;
				return (1);
			}
		}
		if (inter.y < co.center.y - co.separation)
		{
			tmp_1.radius = tmp_1.center.y - co.separation;
			if (disk_calcul(r, tmp_1, t, eye))
			{
				*disk = 3;
				return (1);
			}
		}
	}
	return (0);
}

int		triangle(t_vector r, t_figure tri, double *t, t_vector eye)
{
	t_vector	ab;
	t_vector	ac;
	t_vector	d;
	double		sol;
	double		u;
	double		v;
	double		tmp;

	ab = vecsub(&tri.a, &tri.b);
    ac = vecsub(&tri.a, &tri.c);
    if ((sol = -1 * ab.z * r.y * ac.x + ab.y * r.z * ac.x + r.x * ab.z * ac.y
		+ r.y * ab.x * ac.z - r.z * ab.x * ac.y - r.x * ab.y * ac.z) == 0.00001)
        return (0);
    d = vecsub(&tri.a, &eye);
    v = (-1 * r.x * ab.y * d.z - r.z * ab.x * d.y + ab.y * r.z * d.x
		+ r.x * ab.z * d.y + r.y * ab.x * d.z - ab.z * r.y * d.x) / sol;
    u = -1 * (-1 * r.y * d.x * ac.z + r.y * ac.x * d.z - ac.x * r.z * d.y
		+ d.x * r.z * ac.y - r.x * ac.y * d.z + r.x * d.y * ac.z) / sol;
    tmp = -1 * (-1 * d.x * ab.z * ac.y + d.x * ab.y * ac.z + ab.x * ac.y * d.z
		- ab.x * d.y * ac.z - ac.x * ab.y * d.z + ac.x * ab.z * d.y) / sol;
    if (u > 0.00001 && v > 0.00001 && u + v <= 1 && tmp < *t)
	{
		*t = tmp;
		return (1);
	}
	return (0);
}

int		quadrilateral(t_vector r, t_figure tri, double *t, t_vector eye)
{
	t_figure	part1;
	t_figure	part2;
	int			ret;
	int			ret2;

	part1 = tri;
	part2 = tri;
	part2.a = tri.c;
	part2.b = tri.d;
	part2.c = tri.a;
	ret = triangle(r, part1, t, eye);
	ret2 = triangle(r, part2, t, eye);
	if (ret != ret2)
		ret = (ret == 1) ? ret : ret2;
	return (ret);
}
