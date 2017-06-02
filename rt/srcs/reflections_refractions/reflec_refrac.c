/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflec_refrac.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/06 11:18:24 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/11 18:01:03 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	reflec_refrac(t_env *rt, t_vector ray, t_vector orig)
{
	int	rr;

	rr = 0;
	if (rt->object[rt->i2].material.shiny)
	{
		rt->first_reflec = rt->object[rt->i2].material.reflection;
		reflections(rt, ray, orig, rr);
	}
	if (rt->object[rt->i2].material.transparent)
	{
		rr = 0;
		rt->first_refrac = rt->object[rt->i2].material.refraction;
		rt->prev_refr = rt->object[rt->i2].material.i_refract;
		refractions(rt, ray, orig, rr);
	}
}
