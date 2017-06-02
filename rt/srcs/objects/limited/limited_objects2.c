/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limited_objects2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 11:18:35 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/12 10:25:30 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static gboolean	disk(int i, int *disk)
{
	if (!i)
		*disk = 0;
	if (i == 1)
		*disk = 2;
	if (i == 2)
		*disk = 3;
	return (1);
}

int				limited_cylinder(t_vector r, t_figure cy, t_vector eye,
	t_env *rt)
{
	double		tmp;
	t_figure	tmp_1;
	t_vector	inter;

	tmp = equation_cy(&eye, &r, &cy);
	inter = calcul_ptinter(eye, r, tmp);
	tmp_1 = cy;
	tmp_1.size = cy.radius;
	if (tmp < rt->t && tmp > 0.00001 && inter.y <= cy.center.y + cy.separation
		&& inter.y >= cy.center.y - cy.separation)
	{
		rt->t = tmp;
		return (disk(0, &rt->disk_cy));
	}
	if (inter.y > cy.center.y + cy.separation && (tmp_1.radius = tmp_1.center.y
		+ cy.separation) && disk_calcul(r, tmp_1, &rt->t, eye))
		return (disk(1, &rt->disk_cy));
	if (inter.y < cy.center.y - cy.separation && (tmp_1.radius = tmp_1.center.y
		- cy.separation) && disk_calcul(r, tmp_1, &rt->t, eye))
		return (disk(2, &rt->disk_cy));
	return (0);
}

int				limited_cone(t_vector r, t_figure co, t_vector eye, t_env *rt)
{
	double		tmp;
	t_figure	tmp_1;
	t_vector	inter;

	tmp = equation_co(&eye, &r, &co);
	inter = calcul_ptinter(eye, r, tmp);
	tmp_1 = co;
	tmp_1.size = tan(M_PI / 4) * co.separation;
	if (tmp < rt->t && tmp > 0.00001 && inter.y <= co.center.y + co.separation
		&& inter.y >= co.center.y - co.separation)
	{
		rt->t = tmp;
		return (disk(0, &rt->disk_co));
	}
	if (inter.y < co.center.y - co.separation && (tmp_1.radius = tmp_1.center.y
		- co.separation) && disk_calcul(r, tmp_1, &rt->t, eye))
		return (disk(2, &rt->disk_co));
	if (inter.y > co.center.y + co.separation && (tmp_1.radius = tmp_1.center.y
		+ co.separation) && disk_calcul(r, tmp_1, &rt->t, eye))
		return (disk(1, &rt->disk_co));
	return (0);
}
