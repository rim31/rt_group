/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limited_equations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 11:18:35 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/12 10:26:31 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double			distance_limit(double a, double b, double c)
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
	return (tmp);
}

int				disk_calcul(t_vector r, t_figure d, double *t, t_vector eye)
{
	double		tmp;
	t_vector	inter;

	tmp = -(0 * eye.x - 1 * eye.y + 0 * eye.z + d.radius) /
	(0 * r.x + -1 * r.y + 0 * r.z);
	if (tmp < *t && tmp > 0.00001)
	{
		inter = calcul_ptinter(eye, r, tmp);
		if ((inter.x - d.center.x) * (inter.x - d.center.x) +
			(inter.z - d.center.z) * (inter.z - d.center.z) < d.size * d.size)
		{
			*t = tmp;
			return (1);
		}
	}
	return (0);
}

double			equation_s(t_vector *eye, t_vector *r, t_figure *s)
{
	double		coeff[3];

	*eye = rotations(*eye, s->angle.x, s->angle.y, s->angle.z);
	*r = rotations(*r, s->angle.x, s->angle.y, s->angle.z);
	s->center = rotations(s->center, s->angle.x, s->angle.y, s->angle.z);
	coeff[0] = r->x * r->x + r->y * r->y + r->z * r->z;
	coeff[1] = 2 * (r->x * (eye->x - s->center.x) + r->y *
	(eye->y - s->center.y) + r->z * (eye->z - s->center.z));
	coeff[2] = ((eye->x - s->center.x) * (eye->x - s->center.x) +
	(eye->y - s->center.y) * (eye->y - s->center.y) + (eye->z - s->center.z) *
	(eye->z - s->center.z)) - s->radius * s->radius;
	return (distance_limit(coeff[0], coeff[1], coeff[2]));
}

double			equation_cy(t_vector *eye, t_vector *r, t_figure *cy)
{
	double		coeff[3];

	*eye = rotations(*eye, cy->angle.x, cy->angle.y, cy->angle.z);
	*r = rotations(*r, cy->angle.x, cy->angle.y, cy->angle.z);
	cy->center = rotations(cy->center, cy->angle.x, cy->angle.y, cy->angle.z);
	coeff[0] = r->x * r->x + r->z * r->z;
	coeff[1] = 2 * (r->x * (eye->x - cy->center.x) + r->z *
	(eye->z - cy->center.z));
	coeff[2] = (eye->x - cy->center.x) * (eye->x - cy->center.x) +
	(eye->z - cy->center.z) * (eye->z - cy->center.z) - cy->radius * cy->radius;
	return (distance_limit(coeff[0], coeff[1], coeff[2]));
}

double			equation_co(t_vector *eye, t_vector *r, t_figure *co)
{
	double		coeff[3];

	*eye = rotations(*eye, co->angle.x, co->angle.y, co->angle.z);
	*r = rotations(*r, co->angle.x, co->angle.y, co->angle.z);
	co->center = rotations(co->center, co->angle.x, co->angle.y, co->angle.z);
	coeff[0] = r->x * r->x - r->y * r->y + r->z * r->z;
	coeff[1] = 2 * (r->x * (eye->x - co->center.x) - r->y *
	(eye->y - co->center.y) + r->z * (eye->z - co->center.z));
	coeff[2] = (eye->x - co->center.x) * (eye->x - co->center.x) - (eye->y -
	co->center.y) * (eye->y - co->center.y) + (eye->z - co->center.z) *
	(eye->z - co->center.z);
	return (distance_limit(coeff[0], coeff[1], coeff[2]));
}
