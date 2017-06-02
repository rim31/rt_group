/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limited_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 11:18:35 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/11 19:50:40 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				limited_sphere(t_vector r, t_figure s, t_vector eye, t_env *rt)
{
	double		tmp;
	t_figure	tmp_1;
	t_vector	inter;

	tmp = equation_s(&eye, &r, &s);
	if (tmp < rt->t && tmp > 0.00001)
	{
		inter = calcul_ptinter(eye, r, tmp);
		tmp_1 = s;
		tmp_1.size = sqrt(s.radius * s.radius - s.separation * s.separation);
		tmp_1.radius = tmp_1.center.y + s.separation;
		if (inter.y <= s.center.y + s.separation)
		{
			rt->t = tmp;
			rt->disk_s = 0;
			return (1);
		}
		if (disk_calcul(r, tmp_1, &rt->t, eye))
		{
			rt->disk_s = 2;
			return (1);
		}
	}
	return (0);
}
