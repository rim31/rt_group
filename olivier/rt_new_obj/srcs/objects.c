/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <oseng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/20 15:12:19 by svelhinh          #+#    #+#             */
/*   Updated: 2016/05/10 17:56:33 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	distance(double a, double b, double c, double *t)
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
	return (distance(a, b, c, t));
}

// int			disk(t_vector r, t_figure dis, double *t, t_vector eye)//test
// {
// 	double		tmp;
// 	t_vector inter;
//
// 	// eye = rotations(eye, dis.angle.x, dis.angle.y, dis.angle.z);
// 	// r = rotations(r, dis.angle.x, dis.angle.y, dis.angle.z);
// 	// dis.center = rotations(dis.center, dis.angle.x, dis.angle.y, dis.angle.z);
// 	tmp = -(-dis.center.x * eye.x + dis.center.y * eye.y + dis.center.z *
// 		eye.z + dis.radius) / (-dis.center.x * r.x + dis.center.y * r.y +
// 			dis.center.z * r.z);
// 	if (tmp < *t && tmp > 0.00001)
// 	{
// 		*t = tmp;
// 		inter = calcul_ptinter(eye, r, *t);// mettre les bonne position pour le disque
// 		if ((inter.x - 10) * (inter.x - 10) + (inter.z - 10) * (inter.z - 10) <= 500)//modifier les coordonnees
// 			return (1);
// 	}
// 	return (0);
// }

// int			plane(t_vector r, t_figure p, double *t, t_vector eye)//disk
// {
// 	double		tmp;
// 	t_vector inter;
//
//
// 	tmp = -(-p.center.x * eye.x + p.center.y * eye.y + p.center.z *
// 		eye.z + p.radius) / (-p.center.x * r.x + p.center.y * r.y +
// 			p.center.z * r.z);
// 	if (tmp < *t && tmp > 0.00001)
// 	{
// 		*t = tmp;
// 		inter = calcul_ptinter(eye, r, *t);// mettre les bonne position pour le disque
// 		if ((inter.x - 10) * (inter.x - 10) + (inter.z + 300) * (inter.z + 300) <= 500)//modifier les coordonnees
// 		return (1);
// 	}
// 	return (0);
// }


static t_vector prod_vec(t_vector a, t_vector b)
{
	t_vector ray;

	ray.x = a.y * b.z - a

	retirn(ray);
}

int			plane(t_vector r, t_figure p, double *t, t_vector eye)
{
	double		tmp;
	t_vector a;
	t_vector b;
	t_vector c;
	t_vector ab;
	t_vector ac;
	t_vector bc;

	a.x = 0;
	a.y = 0;
	a.z = 0;
	b.x = 100;
	b.y = 0;
	b.z = 0;
	c.x = 100;
	c.y = 0;
	c.z = 100;
	ab.x = b.x - a.x;
	ab.y = b.y - a.y;
	ab.z = b.z - a.z;
	ac.x = c.x - a.x;
	ac.y = c.y - a.y;
	ac.z = c.z - a.z;
	bc.x = c.x - b.x;
	bc.y = c.y - b.y;
	bc.z = c.z - b.z;


	tmp = -(-p.center.x * eye.x + p.center.y * eye.y + p.center.z *
		eye.z + p.radius) / (-p.center.x * r.x + p.center.y * r.y +
			p.center.z * r.z);
	if (tmp < *t && tmp > 0.00001)
	{
		*t = tmp;
		inter = calcul_ptinter(eye, r, *t);
		return (1);
	}
	return (0);
}

// int			plane(t_vector r, t_figure p, double *t, t_vector eye)
// {
// 	double		tmp;
//
// 	tmp = -(-p.center.x * eye.x + p.center.y * eye.y + p.center.z *
// 		eye.z + p.radius) / (-p.center.x * r.x + p.center.y * r.y +
// 			p.center.z * r.z);
// 	if (tmp < *t && tmp > 0.00001)
// 	{
// 		*t = tmp;
// 		return (1);
// 	}
// 	return (0);
// }

int			cylinder(t_vector r, t_figure cy, double *t, t_vector eye)
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
	return (distance(a, b, c, t));
}

int			cone(t_vector r, t_figure co, double *t, t_vector eye)
{
	double		a;
	double		b;
	double		c;

	eye = rotations(eye, co.angle.x, co.angle.y, co.angle.z);
	r = rotations(r, co.angle.x, co.angle.y, co.angle.z);
	co.center = rotations(co.center, co.angle.x, co.angle.y, co.angle.z);
	a = pow(r.x, 2) - pow(r.y, 2) + pow(r.z, 2);
	b = 2 * (r.x * (eye.x - co.center.x) - r.y * (eye.y - co.center.y) + r.z *
		(eye.z - co.center.z));
	c = (pow(eye.x - co.center.x, 2) - pow(eye.y - co.center.y, 2) +
		pow(eye.z - co.center.z, 2));
	return (distance(a, b, c, t));
}
