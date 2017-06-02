/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <oseng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 15:29:15 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/02 14:36:44 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	parsing_materials(t_material *materials, char *material)
{
	if (!ft_strcmp(material, "mirror"))
	{
		materials->specular = 0;
		materials->specular_power = 0;
		materials->shiny = 1;
		materials->transparent = 0;
		materials->reflection = 0.8;
		materials->refraction = 0;
		materials->i_refract = 0;
	}
	else if (!ft_strcmp(material, "glass"))
	{
		materials->specular = 200;
		materials->specular_power = 200;
		materials->shiny = 1;
		materials->transparent = 0;
		materials->reflection = 1;
		materials->refraction = 0;
		materials->i_refract = 0;
	}
	else if (!ft_strcmp(material, "metal"))
	{
		materials->specular = 600;
		materials->specular_power = 500;
		materials->shiny = 0;
		materials->transparent = 0;
		materials->reflection = 0;
		materials->refraction = 0;
		materials->i_refract = 0;
	}
	else
		ft_exit("\033[31mA defined material does not exist\n");
}

static void	missing_parameter_obj(char **tab)
{
	if (((!ft_strcmp(tab[0], "radius") ||
	!ft_strcmp(tab[0], "material") || !ft_strcmp(tab[0], "separation")) &&
	(!tab[2] || tab[3])) || ((!ft_strcmp(tab[0], "pos") ||
	!ft_strcmp(tab[0], "color") || !ft_strcmp(tab[0], "angle")) &&
	(!tab[2] || !tab[3] || !tab[4] || tab[5])) || ft_strcmp(tab[1], ":"))
			ft_exit("\033[31mWrong format for an object\n");
}

static void	parsing_options(char **tab, t_env *rt, int i)
{
	if (!tab[0] || !tab[1])
		ft_exit("\033[31mWrong format for an object\n");
	missing_parameter_obj(tab);
	if (!ft_strcmp(tab[0], "radius"))
	{
		if (ft_atof(tab[2]) <= 0 && rt->object[i].name != PLANE && rt->object[i].name != HYPERBOL)
			ft_exit("\033[31mRadius must be positive\n");
		rt->object[i].radius = ft_atof(tab[2]);
	}
	else if (!ft_strcmp(tab[0], "pos"))
	{
		rt->object[i].center.x = ft_atof(tab[2]);
		rt->object[i].center.y = ft_atof(tab[3]);
		rt->object[i].center.z = ft_atof(tab[4]);
	}
	else if (!ft_strcmp(tab[0], "color"))
	{
		check_color(ft_atof(tab[2]), ft_atof(tab[3]), ft_atof(tab[4]));
		rt->object[i].color.r = ft_atof(tab[2]);
		rt->object[i].color.g = ft_atof(tab[3]);
		rt->object[i].color.b = ft_atof(tab[4]);
	}
	else if (!ft_strcmp(tab[0], "angle"))
	{
		rt->object[i].angle.x = ft_atof(tab[2]);
		rt->object[i].angle.y = ft_atof(tab[3]);
		rt->object[i].angle.z = ft_atof(tab[4]);
	}
	else if (!ft_strcmp(tab[0], "a"))
	{
		rt->object[i].a.x = ft_atof(tab[2]);
		rt->object[i].a.y = ft_atof(tab[3]);
		rt->object[i].a.z = ft_atof(tab[4]);
	}
	else if (!ft_strcmp(tab[0], "b"))
	{
		rt->object[i].b.x = ft_atof(tab[2]);
		rt->object[i].b.y = ft_atof(tab[3]);
		rt->object[i].b.z = ft_atof(tab[4]);
	}
	else if (!ft_strcmp(tab[0], "c"))
	{
		rt->object[i].c.x = ft_atof(tab[2]);
		rt->object[i].c.y = ft_atof(tab[3]);
		rt->object[i].c.z = ft_atof(tab[4]);
	}
	else if (!ft_strcmp(tab[0], "d"))
	{
		rt->object[i].d.x = ft_atof(tab[2]);
		rt->object[i].d.y = ft_atof(tab[3]);
		rt->object[i].d.z = ft_atof(tab[4]);
	}
	else if (!ft_strcmp(tab[0], "material"))
		parsing_materials(&rt->object[i].material, tab[2]);
	else if (!ft_strcmp(tab[0], "separation"))
		rt->object[i].separation = ft_atof(tab[2]);
	else if (!ft_strcmp(tab[0], "negativ"))
		rt->object[i].negativ = ft_atoi(tab[2]);
	else
		ft_exit("\033[31mWrong option for an object\n");
}

void		parsing_objects(int fd, char *object, t_env *rt)
{
	char		*line;
	char		**tab;
	int			tmp;

	tmp = 0;
	while (get_next_line(fd, &line) > 0 && line[0])
	{
		tmp = 1;
		tab = ft_strsplit(line, ' ');
		if (!tab[2])
			ft_exit("\033[31mMissing parameter for an object\n");
		if (!ft_strcmp(object, "sphere"))
			rt->object[rt->i_obj].name = SPHERE;
		else if (!ft_strcmp(object, "plane"))
			rt->object[rt->i_obj].name = PLANE;
		else if (!ft_strcmp(object, "cylinder"))
			rt->object[rt->i_obj].name = CYLINDER;
		else if (!ft_strcmp(object, "cone"))
			rt->object[rt->i_obj].name = CONE;
		else if (!ft_strcmp(object, "limited_sphere"))
			rt->object[rt->i_obj].name = L_SPHERE;
		else if (!ft_strcmp(object, "limited_cylinder"))
			rt->object[rt->i_obj].name = L_CYLINDER;
		else if (!ft_strcmp(object, "limited_cone"))
			rt->object[rt->i_obj].name = L_CONE;
		else if (!ft_strcmp(object, "triangle"))
			rt->object[rt->i_obj].name = TRIANGLE;
		else if (!ft_strcmp(object, "quadrilateral"))
			rt->object[rt->i_obj].name = QUADRILATERAL;
		else if (!ft_strcmp(object, "torus"))
			rt->object[rt->i_obj].name = TORUS;//torus <============================================================
		else if (!ft_strcmp(object, "quadric"))
			rt->object[rt->i_obj].name = QUADRIC;//quadric <============================================================
		else if (!ft_strcmp(object, "hyperboloid"))
			rt->object[rt->i_obj].name = HYPERBOL;
		else if (!ft_strcmp(object, "light"))
			rt->object[rt->i_obj].name = LIGHT;
		parsing_options(tab, rt, rt->i_obj);
		tab_free(tab);
		ft_strdel(&line);
	}
	if (tmp)
		ft_strdel(&line);
	rt->i_obj++;
}
