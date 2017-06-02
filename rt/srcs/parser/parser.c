/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 15:28:55 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/12 10:33:23 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			parsing(char **tab, t_env *rt)
{
	if (!ft_strcmp(tab[0], "background_color"))
		background_color(tab, rt);
	else if (!ft_strcmp(tab[0], "resolution"))
		resolution(tab, rt);
	else if (!ft_strcmp(tab[0], "reflections"))
	{
		if (tab[3] || !tab[2])
			ft_exit("\033[31mWrong reflections (reflections : max [0-15])\n");
		if (ft_atoi(tab[2]) < 0 || ft_atoi(tab[2]) > 15)
			ft_exit("\033[31mReflections must be between 0 and 15\n");
		rt->max_reflect = ft_atoi(tab[2]);
	}
	else if (!ft_strcmp(tab[0], "refractions"))
	{
		if (tab[3] || !tab[2])
			ft_exit("\033[31mWrong refractions (refractions : max [0-15])\n");
		if (ft_atoi(tab[2]) < 0 || ft_atoi(tab[2]) > 15)
			ft_exit("\033[31mRefractions must be between 0 and 15\n");
		rt->max_refract = ft_atoi(tab[2]);
	}
}

static void			parsing2(char **tab, t_env *rt, int fd)
{
	if (!ft_strcmp(tab[0], "material_type"))
	{
		if (!tab[2] || tab[3])
			ft_exit("\033[31mWrong material (material : [material_name])\n");
		parsing_materials(fd, tab[2], rt);
	}
	else if (!ft_strcmp(tab[0], "object"))
	{
		if (!tab[2] || tab[3])
			ft_exit("\033[31mWrong object (object : [object_name])\n");
		objects(tab[2], rt, fd);
	}
	else if (!ft_strcmp(tab[0], "ambient_light"))
	{
		if (!tab[2] || tab[3] || ft_atof(tab[2]) > 1 || ft_atof(tab[2]) < 0)
			ft_exit("\033[31mWrong ambient light (ambient_light : [0-1])\n");
		rt->ambient = ft_atof(tab[2]);
	}
}

static void			compare(char **tab)
{
	if (!tab[0] || !tab[1] || (ft_strcmp(tab[0], "material_type") &&
ft_strcmp(tab[0], "object") && ft_strcmp(tab[0], "ambient_light") &&
ft_strcmp(tab[0], "background_color") && ft_strcmp(tab[0], "resolution") &&
ft_strcmp(tab[0], "reflections") && ft_strcmp(tab[0], "refractions")))
		ft_exit("\033[31mWrong option\n");
}

void				global_parser(char *file, t_env *rt)
{
	int		fd;
	char	*line;
	char	**tab;

	rt->i_obj = 0;
	rt->i_light = 0;
	rt->i_mat = 0;
	init_all(file, rt);
	if ((fd = open(file, O_RDONLY)) == -1)
		ft_exit("\033[31mThis scene doesn't exist\n");
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0])
		{
			tab = ft_strsplit(line, ' ');
			compare(tab);
			parsing(tab, rt);
			parsing2(tab, rt, fd);
			tab_free(tab);
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
	(close(fd) == -1) ? (ft_exit("\033[31mThis scene failed to close")) : (0);
}
