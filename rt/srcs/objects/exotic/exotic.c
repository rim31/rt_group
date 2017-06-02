/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exotic.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/20 15:12:19 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/12 10:53:42 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		distance(double a, double b, double c, double *t)
{
	double	disc;
	double	sqrt_disc;
	double	t0;
	double	t1;
	double	tmp;

	disc = b * b - 4 * a * c;
	if (disc < 0)
		return (0);
	sqrt_disc = sqrt(disc);
	t0 = (-b - sqrt_disc) / (2 * a);
	t1 = (-b + sqrt_disc) / (2 * a);
	tmp = (t0 < t1) ? (t0) : (t1);
	if (tmp < *t && tmp > 0.00001)
	{
		*t = tmp;
		return (1);
	}
	return (0);
}

int				parabol(t_vector r, t_figure q, double *t, t_vector eye)
{
	double a;
	double b;
	double c;

	q.radius = -3;
	eye = rotations(eye, q.angle.x, q.angle.y, q.angle.z);
	r = rotations(r, q.angle.x, q.angle.y, q.angle.z);
	q.center = rotations(q.center, q.angle.x, q.angle.y, q.angle.z);
	a = pow(r.x, 2) - pow(r.y, 2) + pow(r.z, 2);
	b = 2 * (r.x * (eye.x - q.center.x) - r.y * (eye.y - q.center.y) + r.z *
		(eye.z - q.center.z));
	c = (pow(eye.x - q.center.x, 2) - pow(eye.y - q.center.y, 2) +
		pow(eye.z - q.center.z, 2)) - q.radius;
	return (distance(a, b, c, t));
}

/*
** 2nd degre equation
** A.x^2+ B.y^2 + C.z^2 + D.x.y + E.x.z + F.y.z + G.x + H.y + I.z + J = 0
*/

int				ellipsoide(t_vector r, t_figure el, double *t, t_vector eye)
{
	double	c[3];

	eye = rotations(eye, el.angle.x, el.angle.y, el.angle.z);
	r = rotations(r, el.angle.x, el.angle.y, el.angle.z);
	el.center = rotations(el.center, el.angle.x, el.angle.y, el.angle.z);
	r.y *= 0.5;
	c[0] = r.x * r.x + r.y * r.y + r.z * r.z;
	c[1] = 2 * (r.x * (eye.x - el.center.x) + r.y * (eye.y - el.center.y) +
	r.z * (eye.z - el.center.z));
	c[2] = ((eye.x - el.center.x) * (eye.x - el.center.x) +
	(eye.y - el.center.y) * (eye.y - el.center.y) + (eye.z - el.center.z) *
	(eye.z - el.center.z)) - el.radius * el.radius;
	return (distance(c[0], c[1], c[2], t));
}

static double	solveur4(double a[5], double *t)
{
	double						z[10];
	double						res;
	int							i;
	gsl_poly_complex_workspace	*w;

	res = 0.;
	w = gsl_poly_complex_workspace_alloc(5);
	gsl_poly_complex_solve(a, 5, w, z);
	gsl_poly_complex_workspace_free(w);
	i = 0;
	while (i < 4)
	{
		if (z[2 * i + 1] == 0.0 && (((z[2 * i] < res) ||
		(res == 0.0)) && (z[2 * i] > 0.0)))
			res = z[2 * i];
		i++;
	}
	if (res < *t && res > 0.00001)
	{
		*t = res;
		return (1);
	}
	return (0);
}

/*
** f(x, y, z) = (x2+y2+z2)2 -2(a2+b2)(x2 + y2 + z2) + 4a2y2 + (a2+b2)2;
*/

int				torus(t_vector ray, t_figure to, double *t, t_vector eye)
{
	double		c[5];
	t_vector	k;
	double		e;

	eye = rotations(eye, to.angle.x, to.angle.y, to.angle.z);
	ray = rotations(ray, to.angle.x, to.angle.y, to.angle.z);
	to.center = rotations(to.center, to.angle.x, to.angle.y, to.angle.z);
	k.x = ray.x * ray.x + ray.y * ray.y + ray.z * ray.z;
	e = (eye.x - to.center.x) * (eye.x - to.center.x) + (eye.y - to.center.y) *
	(eye.y - to.center.y) + (eye.z - to.center.z) * (eye.z - to.center.z) -
	to.separation * to.separation - to.radius * to.radius;
	k.z = (eye.x - to.center.x) * ray.x + (eye.y - to.center.y) * ray.y +
	(eye.z - to.center.z) * ray.z;
	k.y = 4.0 * to.separation * to.separation;
	c[0] = e * e - k.y * (to.radius * to.radius - (eye.y - to.center.y) *
	(eye.y - to.center.y));
	c[1] = 4.0 * k.z * e + 2.0 * k.y * (eye.y - to.center.y) * ray.y;
	c[2] = 2.0 * k.x * e + 4.0 * k.z * k.z + k.y * ray.y * ray.y;
	c[3] = 4.0 * k.x * k.z;
	c[4] = k.x * k.x;
	return (solveur4(c, t));
}
