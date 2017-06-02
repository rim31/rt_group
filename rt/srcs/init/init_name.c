/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_name.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grass-kw <grass-kw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 16:31:38 by grass-kw          #+#    #+#             */
/*   Updated: 2016/06/12 10:41:29 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	init_name2(t_env *rt, char *object)
{
	if (!ft_strcmp(object, "ellipsoide"))
		rt->object[rt->i_obj].name = ELLIPSOIDE;
	if (!ft_strcmp(object, "parabol"))
		rt->object[rt->i_obj].name = PARABOL;
	if (!ft_strcmp(object, "cube"))
		rt->object[rt->i_obj].name = CUBE;
	if (!ft_strcmp(object, "cube"))
		rt->object[rt->i_obj].name = CUBE;
	if (!ft_strcmp(object, "light"))
		rt->object[rt->i_obj].name = LIGHT;
	if (!ft_strcmp(object, "light"))
		rt->object[rt->i_obj].name = LIGHT;
}

void		init_name(t_env *rt, char *object)
{
	if (!ft_strcmp(object, "sphere"))
		rt->object[rt->i_obj].name = SPHERE;
	if (!ft_strcmp(object, "plane"))
		rt->object[rt->i_obj].name = PLANE;
	if (!ft_strcmp(object, "cylinder"))
		rt->object[rt->i_obj].name = CYLINDER;
	if (!ft_strcmp(object, "cone"))
		rt->object[rt->i_obj].name = CONE;
	if (!ft_strcmp(object, "limited_sphere"))
		rt->object[rt->i_obj].name = L_SPHERE;
	if (!ft_strcmp(object, "limited_cylinder"))
		rt->object[rt->i_obj].name = L_CYLINDER;
	if (!ft_strcmp(object, "limited_cone"))
		rt->object[rt->i_obj].name = L_CONE;
	if (!ft_strcmp(object, "triangle"))
		rt->object[rt->i_obj].name = TRIANGLE;
	if (!ft_strcmp(object, "quadrilateral"))
		rt->object[rt->i_obj].name = QUADRILATERAL;
	if (!ft_strcmp(object, "hyperboloid"))
		rt->object[rt->i_obj].name = HYPERBOL;
	if (!ft_strcmp(object, "torus"))
		rt->object[rt->i_obj].name = TORUS;
	init_name2(rt, object);
}
