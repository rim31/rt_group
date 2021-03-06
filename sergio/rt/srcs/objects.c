/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/20 15:12:19 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/01 16:59:40 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	obj_neg(t_vector ray, t_vector origin, t_figure *object, int nbobj, double *t)
{
	int		i;

	i = 0;
	while (i < nbobj)
	{
		if (object[i].negativ)
			if (object[i].name == SPHERE && sphere(ray, object[i], t,
					origin))
				return (1);
		i++;
	}
	return (0);
}

static int	distance(double a, double b, double c, double *t)
{
	double	disc;
	double	t0;
	double	t1;
	double	tmp;
	// double	tmp2;

	disc = pow(b, 2) - 4 * a * c;
	if (disc < 0)
		return (0);
	t0 = (-b - sqrt(disc)) / (2 * a);
	t1 = (-b + sqrt(disc)) / (2 * a);
	tmp = (t0 < t1) ? (t0) : (t1);
	// tmp2 = (t0 < t1) ? (t1) : (t0);
	// if (object.negativ && tmp2 < *t)
	// 	return (0);
	if (tmp < *t && tmp > 0.00001)
	{
		*t = tmp;
		return (1);
	}
	return (0);
}

int			sphere(t_vector r, t_figure s, double *t, t_vector eye)
{
	double	a;
	double	b;
	double	c;

	a = pow(r.x, 2) + pow(r.y, 2) + pow(r.z, 2);
	b = 2 * (r.x * (eye.x - s.center.x) + r.y * (eye.y - s.center.y) + r.z *
		(eye.z - s.center.z));
	c = (pow(eye.x - s.center.x, 2) + pow(eye.y - s.center.y, 2) +
		pow(eye.z - s.center.z, 2)) - pow(s.radius, 2);
	// return (distance(a, b, c, t));
	double	disc;
	double	t0;
	double	t1;
	double	tmp;
	double	tmp2;

	disc = pow(b, 2) - 4 * a * c;
	if (disc < 0)
		return (0);
	t0 = (-b - sqrt(disc)) / (2 * a);
	t1 = (-b + sqrt(disc)) / (2 * a);
	tmp = (t0 < t1) ? (t0) : (t1);
	tmp2 = (t0 < t1) ? (t1) : (t0);
	if (s.negativ && tmp2 < *t)
		return (0);
	if (tmp < *t && tmp > 0.00001)
	{
		*t = tmp;
		return (1);
	}
	return (0);
}

int			plane(t_vector r, t_figure p, double *t, t_vector eye)
{
	double		tmp;

	tmp = -(-p.center.x * eye.x + p.center.y * eye.y + p.center.z *
		eye.z + p.radius) / (-p.center.x * r.x + p.center.y * r.y +
			p.center.z * r.z);
	if (tmp < *t && tmp > 0.00001)
	{
		*t = tmp;
		return (1);
	}
	return (0);
}

int			cylinder(t_vector r, t_figure cy, double *t, t_vector eye, t_env *rt)
{
	double		a;
	double		b;
	double		c;

	eye = rotations(eye, cy.angle.x, cy.angle.y, cy.angle.z);
	r = rotations(r, cy.angle.x, cy.angle.y, cy.angle.z);
	cy.center = rotations(cy.center, cy.angle.x, cy.angle.y, cy.angle.z);
	a = pow(r.x, 2) + pow(r.z, 2);
	b = 2 * (r.x * (eye.x - cy.center.x) + r.z * (eye.z - cy.center.z));
	c = pow(eye.x - cy.center.x, 2) + pow(eye.z - cy.center.z, 2) -
		pow(cy.radius, 2);
	// return (distance(a, b, c, t));
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
	if (obj_neg(r, eye, rt->object, rt->nbobj, &tmp))
		return (0);
	if (tmp < *t && tmp > 0.00001)
	{
		*t = tmp;
		return (1);
	}
	return (0);
}

int			cone(t_vector r, t_figure co, double *t, t_vector eye)
{
	double		a;
	double		b;
	double		c;

	if (co.name == CONE)
		co.radius = 0;
	eye = rotations(eye, co.angle.x, co.angle.y, co.angle.z);
	r = rotations(r, co.angle.x, co.angle.y, co.angle.z);
	co.center = rotations(co.center, co.angle.x, co.angle.y, co.angle.z);
	a = pow(r.x, 2) - pow(r.y, 2) + pow(r.z, 2);
	b = 2 * (r.x * (eye.x - co.center.x) - r.y * (eye.y - co.center.y) + r.z *
		(eye.z - co.center.z));
	c = (pow(eye.x - co.center.x, 2) - pow(eye.y - co.center.y, 2) +
		pow(eye.z - co.center.z, 2)) - co.radius;
	return (distance(a, b, c, t));
}
