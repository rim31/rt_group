/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolution.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/19 19:50:01 by lnieto-m          #+#    #+#             */
/*   Updated: 2016/04/27 10:33:40 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		solution(t_env *e, t_vector equ, double *solution)
{
	t_vector	rep;
	double		delta;

	if ((delta = pow(equ.y, 2) - (4 * equ.x * equ.z)) < 0)
		return (0);
	rep.x = ((-1 * equ.y) + sqrt(delta)) / (2 * equ.x);
	rep.y = ((-1 * equ.y) - sqrt(delta)) / (2 * equ.x);
	if (rep.x > rep.y && rep.y >= 0)
		*solution = rep.y;
	else if (rep.x <= rep.y && rep.x >= 0)
		*solution = rep.x;
	else
		return (0);
	if (e->k < *solution && e->k >= 0)
		return (0);
	return (1);
}
