/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <oseng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 15:28:55 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/02 14:47:54 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	background_color(char **color, t_env *rt)
{
	if (color[5] || !color[2] || !color[3] || !color[4])
		ft_exit("\033[31mWrong format for background_color (background_color : r [0-1] g [0-1] b [0-1])\n");
	check_color(ft_atof(color[2]), ft_atof(color[3]), ft_atof(color[4]));
	rt->bg_color.r = ft_atof(color[2]);
	rt->bg_color.g = ft_atof(color[3]);
	rt->bg_color.b = ft_atof(color[4]);
}

static void	objects(char *object, t_env *rt, int fd)
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
		!ft_strcmp(object, "torus") ||/*torus <====================================================================*/
		!ft_strcmp(object, "quadric") ||/*quadric <====================================================================*/
		!ft_strcmp(object, "quadrilateral") ||
		!ft_strcmp(object, "hyperboloid"))
		parsing_objects(fd, object, rt);
	else
		ft_exit("\033[31mA defined object was not found\n");
}

static void	resolution(char **resolution, t_env *rt)
{
	double width;
	double height;

	if (resolution[4] || !resolution[2] || !resolution[3])
		ft_exit("\033[31mWrong format for resolution (resolution : w [0-7680] h [0-4320])\n");
	width = ft_atof(resolution[2]);
	height = ft_atof(resolution[3]);
	if (width > 7680 || width < 640 || height > 4320 || height < 480)
		ft_exit("\033[31mWidth must be between 640 and 7680\nHeight must be between 480 and 4320\n");
	rt->w = width;
	rt->h = height;
}

static void	parsing(char **tab, t_env *rt, int fd)
{
	if (!ft_strcmp(tab[0], "background_color"))
		background_color(tab, rt);
	else if (!ft_strcmp(tab[0], "resolution"))
		resolution(tab, rt);
	else if (!ft_strcmp(tab[0], "reflections"))
	{
		if (tab[3] || !tab[2])
			ft_exit("\033[31mWrong format for reflections (reflections : max [0-15])\n");
		if (ft_atoi(tab[2]) < 0 || ft_atoi(tab[2]) > 15)
			ft_exit("\033[31mReflections must be between 0 and 15\n");
		rt->max_reflect = ft_atoi(tab[2]);
	}
	else if (!ft_strcmp(tab[0], "refractions"))
	{
		if (tab[3] || !tab[2])
			ft_exit("\033[31mWrong format for refractions (refractions : max [0-15])\n");
		if (ft_atoi(tab[2]) < 0 || ft_atoi(tab[2]) > 15)
			ft_exit("\033[31mRefractions must be between 0 and 15\n");
		rt->max_refract = ft_atoi(tab[2]);
	}
	else if (!ft_strcmp(tab[0], "object"))
	{
		if (!tab[2] || tab[3])
			ft_exit("\033[31mWrong format for an object (object : [object_name])\n");
		objects(tab[2], rt, fd);
	}
	else if (!ft_strcmp(tab[0], "ambient_light"))
	{
		if (!tab[2] || tab[3] || ft_atof(tab[2]) > 1 || ft_atof(tab[2]) < 0)
			ft_exit("\033[31mWrong format for ambient light (ambient_light : [0-1])\n");
		rt->ambient = ft_atof(tab[2]);
	}
	else
		ft_exit("\033[31mWrong option\n");
	tab_free(tab);
}

void		global_parser(char *file, t_env *rt)
{
	int		fd;
	char	*line;
	char	**tab;

	rt->i_obj = 0;
	rt->i_light = 0;
	init_all(file, rt);
	if ((fd = open(file, O_RDONLY)) == -1)
		ft_exit("\033[31mThis scene doesn't exist\n");
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0])
		{
			tab = ft_strsplit(line, ' ');
			if (!tab[0] || !tab[1])
				ft_exit("\033[31mWrong option\n");
			parsing(tab, rt, fd);
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
	(close(fd) == -1) ? (ft_exit("\033[31mThis scene failed to close")) : (0);
}
