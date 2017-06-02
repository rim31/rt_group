/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/20 15:12:19 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/11 18:49:54 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	distance(double coeff[3], double *t)
{
	double	disc;
	double	t0;
	double	t1;
	double	tmp;
	double	sqrt_disc;

	disc = coeff[1] * coeff[1] - 4 * coeff[0] * coeff[2];
	if (disc < 0)
		return (0);
	sqrt_disc = sqrt(disc);
	t0 = (-coeff[1] - sqrt_disc) / (2 * coeff[0]);
	t1 = (-coeff[1] + sqrt_disc) / (2 * coeff[0]);
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
	double	coeff[3];

	coeff[0] = r.x * r.x + r.y * r.y + r.z * r.z;
	coeff[1] = 2 * (r.x * (eye.x - s.center.x) + r.y * (eye.y - s.center.y) +
	r.z * (eye.z - s.center.z));
	coeff[2] = ((eye.x - s.center.x) * (eye.x - s.center.x) +
	(eye.y - s.center.y) * (eye.y - s.center.y) + (eye.z - s.center.z) *
	(eye.z - s.center.z)) - s.radius * s.radius;
	return (distance(coeff, t));
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

int			cylinder(t_vector r, t_figure cy, double *t, t_vector eye)
{
	double		coeff[3];

	eye = rotations(eye, cy.angle.x, cy.angle.y, cy.angle.z);
	r = rotations(r, cy.angle.x, cy.angle.y, cy.angle.z);
	cy.center = rotations(cy.center, cy.angle.x, cy.angle.y, cy.angle.z);
	coeff[0] = r.x * r.x + r.z * r.z;
	coeff[1] = 2 * (r.x * (eye.x - cy.center.x) + r.z * (eye.z - cy.center.z));
	coeff[2] = (eye.x - cy.center.x) * (eye.x - cy.center.x) +
	(eye.z - cy.center.z) * (eye.z - cy.center.z) - cy.radius * cy.radius;
	return (distance(coeff, t));
}

int			cone(t_vector r, t_figure co, double *t, t_vector eye)
{
	double		coeff[3];

	if (co.name == CONE)
		co.radius = 0;
	eye = rotations(eye, co.angle.x, co.angle.y, co.angle.z);
	r = rotations(r, co.angle.x, co.angle.y, co.angle.z);
	co.center = rotations(co.center, co.angle.x, co.angle.y, co.angle.z);
	coeff[0] = r.x * r.x - r.y * r.y + r.z * r.z;
	coeff[1] = 2 * (r.x * (eye.x - co.center.x) - r.y * (eye.y - co.center.y) +
	r.z * (eye.z - co.center.z));
	coeff[2] = ((eye.x - co.center.x) * (eye.x - co.center.x) -
	(eye.y - co.center.y) * (eye.y - co.center.y) + (eye.z - co.center.z) *
	(eye.z - co.center.z)) - co.radius;
	return (distance(coeff, t));
}
