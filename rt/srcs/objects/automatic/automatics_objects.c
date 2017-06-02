/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automatics_objects.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/04 12:02:34 by lnieto-m          #+#    #+#             */
/*   Updated: 2016/06/11 18:22:59 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		init_faces(t_figure *face, t_vector *a)
{
	face[0].a = a[0];
	face[0].b = a[1];
	face[0].c = a[3];
	face[1].a = a[5];
	face[1].b = a[6];
	face[1].c = a[4];
	face[2].a = a[0];
	face[2].b = a[1];
	face[2].c = a[5];
	face[3].a = a[1];
	face[3].b = a[6];
	face[3].c = a[2];
	face[4].a = a[2];
	face[4].b = a[7];
	face[4].c = a[3];
	face[5].a = a[3];
	face[5].b = a[4];
	face[5].c = a[0];
}

static void		init_points(t_figure *cube, t_vector *a)
{
	t_vector	center;
	t_vector	p;
	t_vector	m;

	center = rotations(cube->center, cube->angle.x, cube->angle.y,
		cube->angle.z);
	p.x = center.x + cube->radius / 2;
	p.y = center.y + cube->radius / 2;
	p.z = center.z + cube->radius / 2;
	m.x = center.x - cube->radius / 2;
	m.y = center.y - cube->radius / 2;
	m.z = center.z - cube->radius / 2;
	a[0] = new_vector(p.x, p.y, m.z);
	a[1] = new_vector(p.x, p.y, p.z);
	a[2] = new_vector(p.x, m.y, p.z);
	a[3] = new_vector(p.x, m.y, m.z);
	a[4] = new_vector(m.x, m.y, m.z);
	a[5] = new_vector(m.x, p.y, m.z);
	a[6] = new_vector(m.x, p.y, p.z);
	a[7] = new_vector(m.x, m.y, p.z);
}

static int		iter(int tmp, t_figure *cube, t_figure face)
{
	if (tmp && cube->shadows == 0)
	{
		cube->a = face.a;
		cube->b = face.b;
		cube->c = face.c;
	}
	return (tmp);
}

int				cube(t_vector r, t_figure *cube, double *t, t_vector eye)
{
	t_vector	*a;
	t_figure	*face;
	int			ret;
	int			tmp;
	int			i;

	if (!(face = (t_figure *)malloc(sizeof(t_figure) * 6))
		|| !(a = (t_vector *)malloc(sizeof(t_vector) * 8)))
		return (-1);
	tmp = 0;
	ret = 0;
	init_points(cube, a);
	init_faces(face, a);
	eye = rotations(eye, cube->angle.x, cube->angle.y, cube->angle.z);
	r = rotations(r, cube->angle.x, cube->angle.y, cube->angle.z);
	i = 0;
	while (i < 6)
	{
		tmp = quadrilateral(r, face[i], t, eye);
		ret += iter(tmp, cube, face[i]);
		i++;
	}
	free(face);
	free(a);
	return (ret);
}
