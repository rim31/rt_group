/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_options.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/11 16:38:36 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/13 15:49:43 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		background_color(char **color, t_env *rt)
{
	if (color[5] || !color[2] || !color[3] || !color[4])
		ft_exit("\033[31mWrong background_color (r [0-1] g [0-1] b [0-1])\n");
	check_color(ft_atof(color[2]), ft_atof(color[3]), ft_atof(color[4]));
	rt->bg_color.r = ft_atof(color[2]);
	rt->bg_color.g = ft_atof(color[3]);
	rt->bg_color.b = ft_atof(color[4]);
}

void		objects(char *object, t_env *rt, int fd)
{
	if (!ft_strcmp(object, "camera"))
		parsing_camera(fd, rt);
	else if (!ft_strcmp(object, "light"))
		parsing_light(fd, rt);
	else if (!ft_strcmp(object, "sphere") ||
		!ft_strcmp(object, "plane") || !ft_strcmp(object, "cylinder") ||
		!ft_strcmp(object, "cone") || !ft_strcmp(object, "limited_sphere") ||
		!ft_strcmp(object, "limited_cylinder") ||
		!ft_strcmp(object, "limited_cone") ||
		!ft_strcmp(object, "triangle") ||
		!ft_strcmp(object, "quadrilateral") ||
		!ft_strcmp(object, "torus") ||
		!ft_strcmp(object, "parabol") ||
		!ft_strcmp(object, "ellipsoide") ||
		!ft_strcmp(object, "cube") ||
		!ft_strcmp(object, "hyperboloid"))
		parsing_objects(fd, object, rt);
	else
		ft_exit("\033[31mA defined object was not found\n");
}

void		resolution(char **resolution, t_env *rt)
{
	double width;
	double height;

	if (resolution[4] || !resolution[2] || !resolution[3])
		ft_exit("\033[31mWrong resolution (w [0-7680] h [0-4320])\n");
	width = ft_atof(resolution[2]);
	height = ft_atof(resolution[3]);
	if (width > 7680 || width < 640 || height > 4320 || height < 480)
		ft_exit("\033[31mWidth [640-7680]\nHeight [480-4320]\n");
	rt->w = width;
	rt->h = height;
}
