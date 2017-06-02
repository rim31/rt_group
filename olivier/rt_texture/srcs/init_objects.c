/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <oseng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 15:28:12 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/02 14:48:20 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	init_objects(t_env *rt)
{
	int i;

	i = 0;
	while (i < rt->nbobj)
	{
		rt->object[i].name = SPHERE;
		rt->object[i].radius = 30;
		rt->object[i].center.x = 0;
		rt->object[i].center.y = 0;
		rt->object[i].center.z = 0;
		rt->object[i].color.r = 1;
		rt->object[i].color.g = 1;
		rt->object[i].color.b = 1;
		rt->object[i].angle.x = 0;
		rt->object[i].angle.y = 0;
		rt->object[i].angle.z = 0;
		rt->object[i].size = 0;
		rt->object[i].a.x = 0;
		rt->object[i].a.y = 0;
		rt->object[i].a.z = 0;
		rt->object[i].b.x = 0;
		rt->object[i].b.y = 0;
		rt->object[i].b.z = 0;
		rt->object[i].c.x = 0;
		rt->object[i].c.y = 0;
		rt->object[i].c.z = 0;
		rt->object[i].d.x = 0;
		rt->object[i].d.y = 0;
		rt->object[i].d.z = 0;
		rt->object[i].negativ = 0;
		// rt->object[i].disk = 0;
		rt->object[i].separation = 0;
		rt->object[i].material.specular = 0;
		rt->object[i].material.specular_power = 0;
		rt->object[i].material.shiny = 0;
		rt->object[i].material.transparent = 0;
		rt->object[i].material.reflection = 0;
		rt->object[i].material.refraction = 0;
		rt->object[i].material.i_refract = 0;
		i++;
	}
}

void		count_objects(t_env *rt, char *file)
{
	int		fd;
	char	*line;
	int		tmp;

	if ((fd = open(file, O_RDONLY)) == -1)
		ft_exit("\033[31mThis scene doesn't exist\n");
	tmp = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (!ft_strcmp(line, "object : sphere") ||
			!ft_strcmp(line, "object : plane") ||
			!ft_strcmp(line, "object : cylinder") ||
			!ft_strcmp(line, "object : cone") ||
			!ft_strcmp(line, "object : limited_sphere") ||
			!ft_strcmp(line, "object : limited_cylinder") ||
			!ft_strcmp(line, "object : limited_cone") ||
			!ft_strcmp(line, "object : triangle") ||
			!ft_strcmp(line, "object : quadrilateral") ||
			!ft_strcmp(line, "object : torus") || //torus <==============================================
			!ft_strcmp(line, "object : quadric") || //quadric <==============================================
			!ft_strcmp(line, "object : hyperboloid"))
		{
			rt->nbobj++;
			tmp = (!tmp) ? (1) : (tmp);
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
	(close(fd) == -1) ? (ft_exit("\033[31mThis scene failed to close")) : (0);
	if (!tmp)
	{
		tmp++;
		rt->nbobj = 1;
	}
	if (!(rt->object = (t_figure *)malloc(sizeof(t_figure) * rt->nbobj)))
		ft_exit("malloc of rt->object failed in count_objects");
	init_objects(rt);
}
