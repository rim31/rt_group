/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_camera_light.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 15:29:03 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/13 15:50:39 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static char	**split_tab(char *line)
{
	char **tab;

	tab = ft_strsplit(line, ' ');
	missing_parameter(tab);
	return (tab);
}

void		parsing_camera(int fd, t_env *rt)
{
	char	*line;
	char	**tab;
	int		tmp;

	tmp = 0;
	while (get_next_line(fd, &line) > 0 && line[0] != '\0')
	{
		tmp = 1;
		tab = split_tab(line);
		if (!ft_strcmp(tab[0], "pos"))
		{
			rt->eye.x = ft_atof(tab[2]);
			rt->eye.y = ft_atof(tab[3]);
			rt->eye.z = ft_atof(tab[4]);
		}
		else if (!ft_strcmp(tab[0], "angle"))
			rt->cam_angle = new_vector(ft_atof(tab[2]),
			ft_atof(tab[3]), ft_atof(tab[4]));
		tab_free(tab);
		ft_strdel(&line);
	}
	if (tmp)
		ft_strdel(&line);
}

void		parsing_light(int fd, t_env *rt)
{
	char		*line;
	char		**tab;
	int			tmp;

	tmp = 0;
	while (get_next_line(fd, &line) > 0 && line[0] != '\0')
	{
		tab = split_tab(line);
		if (!ft_strcmp(tab[0], "pos"))
			rt->light[rt->i_light].center = new_vector(ft_atof(tab[2]),
			ft_atof(tab[3]), ft_atof(tab[4]));
		else if (!ft_strcmp(tab[0], "color"))
		{
			check_color(ft_atof(tab[2]), ft_atof(tab[3]), ft_atof(tab[4]));
			rt->light[rt->i_light].color.r = ft_atof(tab[2]);
			rt->light[rt->i_light].color.g = ft_atof(tab[3]);
			rt->light[rt->i_light].color.b = ft_atof(tab[4]);
		}
		else if (!ft_strcmp(tab[0], "parallel"))
			rt->light[rt->i_light].parallel = ft_atoi(tab[2]);
		tab_free(tab);
		ft_strdel(&line);
	}
	(tmp) ? (ft_strdel(&line)) : (0);
	rt->i_light++;
}
