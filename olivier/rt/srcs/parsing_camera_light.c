/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_camera_light.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 15:29:03 by svelhinh          #+#    #+#             */
/*   Updated: 2016/04/29 11:26:31 by svelhinh         ###   ########.fr       */
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
	char *line;
	char **tab;

	while (get_next_line(fd, &line) > 0 && line[0] != '\0')
	{
		tab = split_tab(line);
		if (!ft_strcmp(tab[0], "pos"))
		{
			rt->eye.x = ft_atof(tab[2]);
			rt->eye.y = ft_atof(tab[3]);
			rt->eye.z = ft_atof(tab[4]);
		}
		else if (!ft_strcmp(tab[0], "angle"))
		{
			rt->cam_angle.x = ft_atof(tab[2]);
			rt->cam_angle.y = ft_atof(tab[3]);
			rt->cam_angle.z = ft_atof(tab[4]);
		}
		tab_free(tab);
		ft_strdel(&line);
	}
	ft_strdel(&line);
}

void		parsing_light(int fd, t_env *rt)
{
	char		*line;
	char		**tab;
	static int	i;

	while (get_next_line(fd, &line) > 0 && line[0] != '\0')
	{
		tab = split_tab(line);
		if (!ft_strcmp(tab[0], "pos"))
		{
			rt->light[i].center.x = ft_atof(tab[2]);
			rt->light[i].center.y = ft_atof(tab[3]);
			rt->light[i].center.z = ft_atof(tab[4]);
		}
		else if (!ft_strcmp(tab[0], "color"))
		{
			check_color(ft_atof(tab[2]), ft_atof(tab[3]), ft_atof(tab[4]));
			rt->light[i].color.r = ft_atof(tab[2]);
			rt->light[i].color.g = ft_atof(tab[3]);
			rt->light[i].color.b = ft_atof(tab[4]);
		}
		tab_free(tab);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	i++;
}
