/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_camera_light.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 15:29:03 by svelhinh          #+#    #+#             */
/*   Updated: 2016/04/27 15:15:41 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	parsing_camera(int fd, t_env *rt)
{
	char *line;
	char **line2;

	while (get_next_line(fd, &line) > 0 && line[0] != '\0')
	{
		line2 = ft_strsplit(line, ' ');
		missing_parameter(line2);
		if (!ft_strcmp(line2[0], "pos"))
		{
			rt->eye.x = ft_atof(line2[2]);
			rt->eye.y = ft_atof(line2[3]);
			rt->eye.z = ft_atof(line2[4]);
		}
		else if (!ft_strcmp(line2[0], "angle"))
		{
			rt->cam_angle.x = ft_atof(line2[2]);
			rt->cam_angle.y = ft_atof(line2[3]);
			rt->cam_angle.z = ft_atof(line2[4]);
		}
		// line2_free(line2);
		ft_strdel(&line);
	}
}

void	parsing_light(int fd, t_env *rt)
{
	char		*line;
	char		**line2;
	static int	i;

	while (get_next_line(fd, &line) > 0 && line[0] != '\0')
	{
		line2 = ft_strsplit(line, ' ');
		missing_parameter(line2);
		if (!ft_strcmp(line2[0], "pos"))
		{
			rt->light[i].center.x = ft_atof(line2[2]);
			rt->light[i].center.y = ft_atof(line2[3]);
			rt->light[i].center.z = ft_atof(line2[4]);
		}
		else if (!ft_strcmp(line2[0], "color"))
		{
			check_color(ft_atof(line2[2]), ft_atof(line2[3]), ft_atof(line2[4]));
			rt->light[i].color.r = ft_atof(line2[2]);
			rt->light[i].color.g = ft_atof(line2[3]);
			rt->light[i].color.b = ft_atof(line2[4]);
		}
		// line2_free(line2);
		ft_strdel(&line);
	}
	i++;
}
