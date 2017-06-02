/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 10:01:53 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/12 17:58:40 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**	vecs[0] = ray_light
**	vecs[1] = inter
*/

static gboolean		intersect(t_env *rt, t_vector vecs[2], double *t, int i)
{
	if ((rt->object[i].name == SPHERE && sphere(vecs[0], rt->object[i], t,
vecs[1])) || (rt->object[i].name == PLANE && plane(vecs[0], rt->object[i], t,
vecs[1])) || (rt->object[i].name == CYLINDER && cylinder(vecs[0], rt->object[i],
t, vecs[1])) || ((rt->object[i].name == CONE ||
rt->object[i].name == HYPERBOL) && cone(vecs[0], rt->object[i], t, vecs[1])) ||
(rt->object[i].name == L_SPHERE && limited_sphere(vecs[0], rt->object[i],
vecs[1], rt)) || (rt->object[i].name == L_CYLINDER && limited_cylinder(vecs[0],
rt->object[i], vecs[1], rt)) || (rt->object[i].name == L_CONE &&
limited_cone(vecs[0], rt->object[i], vecs[1], rt)) || (rt->object[i].name ==
TRIANGLE && triangle(vecs[0], rt->object[i], t, vecs[1])) ||
(rt->object[i].name == QUADRILATERAL && quadrilateral(vecs[0], rt->object[i], t,
vecs[1])) || (rt->object[i].name == PARABOL && parabol(vecs[0], rt->object[i],
t, vecs[1])) || (rt->object[i].name == CUBE && cube(vecs[0], &rt->object[i], t,
vecs[1])) || (rt->object[i].name == ELLIPSOIDE && ellipsoide(vecs[0],
rt->object[i], t, vecs[1])))
		return (1);
	return (0);
}

static void			init(int *i, double *t, t_env *rt)
{
	*i = 0;
	*t = 1;
	rt->disk_s = 0;
	rt->disk_cy = 0;
	rt->disk_co = 0;
	rt->t = 1;
}

static gboolean		replace(t_env *rt, double t_tmp, int disk[3], int i)
{
	if (rt->object[i].name == L_SPHERE ||
	rt->object[i].name == L_CYLINDER || rt->object[i].name == L_CONE)
	{
		rt->t = t_tmp;
		rt->disk_s = disk[0];
		rt->disk_cy = disk[1];
		rt->disk_co = disk[2];
	}
	return (1);
}

int					shadows(t_env *rt, t_vector ray_light, t_vector inter)
{
	int			i;
	double		t;
	double		t_tmp;
	int			disk[3];
	t_vector	vecs[2];

	disk[0] = rt->disk_s;
	disk[1] = rt->disk_cy;
	disk[2] = rt->disk_co;
	t_tmp = rt->t;
	vecs[0] = ray_light;
	vecs[1] = inter;
	init(&i, &t, rt);
	while (i < rt->nbobj)
	{
		rt->object[i].shadows = 1;
		if (intersect(rt, vecs, &t, i) && replace(rt, t_tmp, disk, i))
			return (1);
		i++;
	}
	rt->t = t_tmp;
	rt->disk_s = disk[0];
	rt->disk_cy = disk[1];
	rt->disk_co = disk[2];
	return (0);
}
