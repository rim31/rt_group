/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_camera_light.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 15:29:03 by svelhinh          #+#    #+#             */
/*   Updated: 2016/05/20 13:48:42 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		print_tab(char **s)
{
	int i;

	i = 0;
	while (s[i] != NULL)
		ft_putendl(s[i++]);
}

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
		{
			rt->cam_angle.x = ft_atof(tab[2]);
			rt->cam_angle.y = ft_atof(tab[3]);
			rt->cam_angle.z = ft_atof(tab[4]);
		}
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
	int		tmp;

	tmp = 0;
	while (get_next_line(fd, &line) > 0 && line[0] != '\0')
	{
		tab = split_tab(line);
		if (!ft_strcmp(tab[0], "pos"))
		{
			rt->light[rt->i_light].center.x = ft_atof(tab[2]);
			rt->light[rt->i_light].center.y = ft_atof(tab[3]);
			rt->light[rt->i_light].center.z = ft_atof(tab[4]);
		}
		else if (!ft_strcmp(tab[0], "color"))
		{
			check_color(ft_atof(tab[2]), ft_atof(tab[3]), ft_atof(tab[4]));
			rt->light[rt->i_light].color.r = ft_atof(tab[2]);
			rt->light[rt->i_light].color.g = ft_atof(tab[3]);
			rt->light[rt->i_light].color.b = ft_atof(tab[4]);
		}
		tab_free(tab);
		ft_strdel(&line);
	}
	if (tmp)
		ft_strdel(&line);
	rt->i_light++;
}
