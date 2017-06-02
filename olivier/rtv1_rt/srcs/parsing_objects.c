/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 15:29:15 by svelhinh          #+#    #+#             */
/*   Updated: 2016/04/27 11:45:40 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	parsing_objects(int fd, char *object, t_env *rt)
{
	static int	i;
	char		*line;
	char		**line2;

	while (get_next_line(fd, &line) > 0 && line[0])
	{
		line2 = ft_strsplit(line, ' ');
		if (!line2[2])
			ft_exit("\033[31mMissing parameter for an object\n");
		if (!ft_strcmp(object, "sphere"))
			rt->object[i].name = SPHERE;
		else if (!ft_strcmp(object, "plane"))
			rt->object[i].name = PLANE;
		else if (!ft_strcmp(object, "cylinder"))
			rt->object[i].name = CYLINDER;
		else if (!ft_strcmp(object, "cone"))
			rt->object[i].name = CONE;
		else if (!ft_strcmp(object, "light"))
			rt->object[i].name = LIGHT;
		if (!ft_strcmp(line2[0], "radius"))
			rt->object[i].radius = ft_atof(line2[2]);
		else if (!ft_strcmp(line2[0], "pos"))
		{
			rt->object[i].center.x = ft_atof(line2[2]);
			rt->object[i].center.y = ft_atof(line2[3]);
			rt->object[i].center.z = ft_atof(line2[4]);
		}
		else if (!ft_strcmp(line2[0], "color"))
		{
			check_color(ft_atof(line2[2]), ft_atof(line2[3]), ft_atof(line2[4]));
			rt->object[i].color.r = ft_atof(line2[2]);
			rt->object[i].color.g = ft_atof(line2[3]);
			rt->object[i].color.b = ft_atof(line2[4]);
		}
		else if (!ft_strcmp(line2[0], "angle"))
		{
			rt->object[i].angle.x = ft_atof(line2[2]);
			rt->object[i].angle.y = ft_atof(line2[3]);
			rt->object[i].angle.z = ft_atof(line2[4]);
		}
		// line2_free(line2);
		ft_strdel(&line);
	}
	i++;
}
