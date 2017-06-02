/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 15:28:12 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/12 10:41:35 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		init_objects(t_env *rt)
{
	int i;

	i = 0;
	while (i < rt->nbobj)
	{
		ft_bzero(&(rt->object[i]), sizeof(t_figure));
		rt->object[i].name = SPHERE;
		rt->object[i].radius = 30;
		rt->object[i].color.r = 1;
		rt->object[i].color.g = 1;
		rt->object[i].color.b = 1;
		rt->object[i].separation = 100;
		rt->object[i].material.name = "nope";
		rt->object[i].material.texture.path = "\0";
		i++;
	}
}

static gboolean	compare(char *line)
{
	if (!ft_strcmp(line, "object : sphere") ||
		!ft_strcmp(line, "object : plane") ||
		!ft_strcmp(line, "object : cylinder") ||
		!ft_strcmp(line, "object : cone") ||
		!ft_strcmp(line, "object : limited_sphere") ||
		!ft_strcmp(line, "object : limited_cylinder") ||
		!ft_strcmp(line, "object : limited_cone") ||
		!ft_strcmp(line, "object : triangle") ||
		!ft_strcmp(line, "object : torus") ||
		!ft_strcmp(line, "object : ellipsoide") ||
		!ft_strcmp(line, "object : parabol") ||
		!ft_strcmp(line, "object : quadrilateral") ||
		!ft_strcmp(line, "object : cube") ||
		!ft_strcmp(line, "object : hyperboloid"))
		return (1);
	return (0);
}

void			count_objects(t_env *rt, char *file)
{
	int		fd;
	char	*line;
	int		tmp;

	if ((fd = open(file, O_RDONLY)) == -1)
		ft_exit("\033[31mThis scene doesn't exist\n");
	tmp = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (compare(line))
		{
			rt->nbobj++;
			tmp = (!tmp) ? (1) : (tmp);
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
	(close(fd) == -1) ? (ft_exit("\033[31mThis scene failed to close")) : (0);
	if (!tmp)
		rt->nbobj = 1;
	if (!(rt->object = (t_figure *)malloc(sizeof(t_figure) * rt->nbobj)))
		ft_exit("malloc of rt->object failed in count_objects");
	init_objects(rt);
}
