/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/17 14:43:38 by lnieto-m          #+#    #+#             */
/*   Updated: 2016/04/20 17:56:50 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		big_shadow(t_env *e, t_vector inter)
{
	if (s_shadow(inter, e, e->sphere) == 1 ||
		s_shadow(inter, e, e->sphere1) == 1 ||
		s_shadow(inter, e, e->sphere2) == 1 ||
		s_shadow(inter, e, e->sphere3) == 1 ||
		s_shadow(inter, e, e->sphere4) == 1 ||
		s_shadow(inter, e, e->sphere5) == 1 ||
		s_shadow(inter, e, e->sphere6) == 1 ||
		s_shadow(inter, e, e->sphere7) == 1 ||
		s_shadow(inter, e, e->sphere8) == 1 ||
		cy_shadow(inter, e, e->cylindre) == 1 ||
		cy_shadow(inter, e, e->cylindre2) == 1 ||
		cy_shadow(inter, e, e->cylindre3) == 1 ||
		cy_shadow(inter, e, e->cylindre4) == 1)
		return (1);
	return (0);
}

int		shadow2(t_env *e, t_vector inter)
{
	if (s_shadow(inter, e, e->sphere1) == 1 ||
		s_shadow(inter, e, e->sphere2) == 1 ||
		s_shadow(inter, e, e->sphere3) == 1 ||
		cy_shadow(inter, e, e->cylindre) == 1 ||
		co_shadow(inter, e, e->cone) == 1)
		return (1);
	return (0);
}

int		shadow(t_env *e, t_vector inter)
{
	if (s_shadow(inter, e, e->sphere1) == 1 ||
		cy_shadow(inter, e, e->cylindre) == 1 ||
		co_shadow(inter, e, e->cone) == 1)
		return (1);
	return (0);
}
