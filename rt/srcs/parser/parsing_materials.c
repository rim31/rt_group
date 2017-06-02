/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_materials.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 15:29:15 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/13 15:53:03 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	missing_parameter_mat(char **tab)
{
	if (((!ft_strcmp(tab[0], "specular") ||
	!ft_strcmp(tab[0], "specular_power") || !ft_strcmp(tab[0], "shiny")
	|| !ft_strcmp(tab[0], "transparent") || !ft_strcmp(tab[0], "reflection") ||
	!ft_strcmp(tab[0], "refraction") || !ft_strcmp(tab[0], "i_refract")) &&
	tab[3]) || ((!ft_strcmp(tab[0], "texture")) &&
tab[4]) || (!ft_strcmp(tab[0], "procedural") && !ft_strcmp(tab[2], "random") &&
tab[3]) || (!ft_strcmp(tab[0], "procedural") && ft_strcmp(tab[2], "random") &&
	tab[10]) || ft_strcmp(tab[1], ":"))
		ft_exit("\033[31mWrong format for a material\n");
}

static void	parsing_reflec_refrac(char **tab, t_material *materials, int i_mat)
{
	if (!ft_strcmp(tab[0], "specular"))
		materials[i_mat].specular = ft_atof(tab[2]);
	else if (!ft_strcmp(tab[0], "specular_power"))
		materials[i_mat].specular_power = ft_atof(tab[2]);
	else if (!ft_strcmp(tab[0], "shiny"))
		materials[i_mat].shiny = ft_atoi(tab[2]);
	else if (!ft_strcmp(tab[0], "transparent"))
		materials[i_mat].transparent = ft_atoi(tab[2]);
	else if (!ft_strcmp(tab[0], "reflection"))
		materials[i_mat].reflection = ft_atof(tab[2]);
	else if (!ft_strcmp(tab[0], "refraction"))
		materials[i_mat].refraction = ft_atof(tab[2]);
	else if (!ft_strcmp(tab[0], "i_refract"))
		materials[i_mat].i_refract = ft_atof(tab[2]);
}

static void	parsing_procedural(char **tab, t_material *materials, int i_mat)
{
	if (!ft_strcmp(tab[0], "procedural"))
	{
		if (!ft_strcmp(tab[2], "bricks"))
			materials[i_mat].procedural.active = BRICKS;
		if (!ft_strcmp(tab[2], "random"))
			materials[i_mat].procedural.active = RANDOM;
		else
		{
			materials[i_mat].procedural.scale = ATOF(3);
			check_color(ATOF(4), ATOF(5), ATOF(6));
			check_color(ATOF(7), ATOF(8), ATOF(9));
			materials[i_mat].procedural.color1 = new_color(ATOF(4),
			ATOF(5), ATOF(6));
			materials[i_mat].procedural.color2 = new_color(ATOF(7),
			ATOF(8), ATOF(9));
		}
	}
}

static void	parsing_options(char **tab, t_env *rt)
{
	GdkPixbuf	*gb;

	if (!tab[0] || !tab[1])
		ft_exit("\033[31mWrong format for a material\n");
	missing_parameter_mat(tab);
	parsing_reflec_refrac(tab, rt->materials, rt->i_mat);
	if (!ft_strcmp(tab[0], "texture"))
	{
		rt->materials[rt->i_mat].texture.path = ft_strdup(tab[2]);
		if (open(tab[2], O_RDONLY) == -1)
			ft_exit("\033[31mA defined texture doesn't exist\n");
		gb = gdk_pixbuf_new_from_file(tab[2], NULL);
		if (!gb)
			ft_exit("\033[31mA defined texture doesn't exist\n");
		rt->materials[rt->i_mat].texture.width = gdk_pixbuf_get_width(gb);
		rt->materials[rt->i_mat].texture.height = gdk_pixbuf_get_height(gb);
		rt->materials[rt->i_mat].texture.row = gdk_pixbuf_get_rowstride(gb);
		rt->materials[rt->i_mat].texture.scale = ft_atof(tab[3]);
		rt->materials[rt->i_mat].texture.buffer = gdk_pixbuf_get_pixels(gb);
		rt->materials[rt->i_mat].texture.alpha = gdk_pixbuf_get_has_alpha(gb);
	}
	parsing_procedural(tab, rt->materials, rt->i_mat);
}

void		parsing_materials(int fd, char *material, t_env *rt)
{
	char		*line;
	char		**tab;
	int			tmp;

	tmp = 0;
	rt->materials[rt->i_mat].name = ft_strdup(material);
	while (get_next_line(fd, &line) > 0 && line[0])
	{
		tmp = 1;
		tab = ft_strsplit(line, ' ');
		if ((ft_strcmp(tab[0], "specular") &&
		ft_strcmp(tab[0], "specular_power") && ft_strcmp(tab[0], "shiny") &&
		ft_strcmp(tab[0], "transparent") && ft_strcmp(tab[0], "reflection") &&
		ft_strcmp(tab[0], "refraction") && ft_strcmp(tab[0], "i_refract") &&
		ft_strcmp(tab[0], "procedural") && ft_strcmp(tab[0], "texture")) ||
		!tab[2])
			ft_exit("\033[31mWrong option for a material\n");
		parsing_options(tab, rt);
		tab_free(tab);
		ft_strdel(&line);
	}
	if (tmp)
		ft_strdel(&line);
	rt->i_mat++;
}
