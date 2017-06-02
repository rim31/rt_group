/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grass-kw <grass-kw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 15:29:15 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/11 18:52:19 by grass-kw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	parsing_options2(char **tab, t_env *rt, int i)
{
	if (!ft_strcmp(tab[0], "angle"))
		rt->object[i].angle = new_vector(ATOF(2), ATOF(3), ATOF(4));
	else if (!ft_strcmp(tab[0], "a"))
		rt->object[i].a = new_vector(ATOF(2), ATOF(3), ATOF(4));
	else if (!ft_strcmp(tab[0], "b"))
		rt->object[i].b = new_vector(ATOF(2), ATOF(3), ATOF(4));
	else if (!ft_strcmp(tab[0], "c"))
		rt->object[i].c = new_vector(ATOF(2), ATOF(3), ATOF(4));
	else if (!ft_strcmp(tab[0], "material"))
		parsing_material(rt, &rt->object[i].material, tab[2]);
	else if (!ft_strcmp(tab[0], "separation"))
		rt->object[i].separation = ATOF(2);
}

static void	parsing_options(char **tab, t_env *rt, int i)
{
	if (!tab[0] || !tab[1])
		ft_exit("\033[31mWrong format for an object\n");
	missing_parameter_obj(tab);
	if (!ft_strcmp(tab[0], "radius"))
	{
		if (ATOF(2) <= 0 && rt->object[i].name != PLANE &&
		rt->object[i].name != HYPERBOL)
			ft_exit("\033[31mRadius must be positive\n");
		rt->object[i].radius = ATOF(2);
	}
	else if (!ft_strcmp(tab[0], "pos"))
		rt->object[i].center = new_vector(ATOF(2), ATOF(3), ATOF(4));
	else if (!ft_strcmp(tab[0], "color"))
	{
		check_color(ATOF(2), ATOF(3), ATOF(4));
		rt->object[i].color = new_color(ATOF(2), ATOF(3), ATOF(4));
	}
}

void		parsing_objects(int fd, char *object, t_env *rt)
{
	char		*line;
	char		**tab;
	int			tmp;

	tmp = 0;
	init_name(rt, object);
	while (get_next_line(fd, &line) > 0 && line[0])
	{
		tmp = 1;
		tab = ft_strsplit(line, ' ');
		if ((ft_strcmp(tab[0], "radius") && ft_strcmp(tab[0], "pos") &&
		ft_strcmp(tab[0], "color") && ft_strcmp(tab[0], "angle") &&
		ft_strcmp(tab[0], "a") && ft_strcmp(tab[0], "b") &&
		ft_strcmp(tab[0], "c") && ft_strcmp(tab[0], "material") &&
		ft_strcmp(tab[0], "separation")) ||
		!tab[2])
			ft_exit("\033[31mMissing parameter for an object\n");
		parsing_options(tab, rt, rt->i_obj);
		parsing_options2(tab, rt, rt->i_obj);
		tab_free(tab);
		ft_strdel(&line);
	}
	if (tmp)
		ft_strdel(&line);
	rt->i_obj++;
}
