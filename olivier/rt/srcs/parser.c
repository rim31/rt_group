/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 15:28:55 by svelhinh          #+#    #+#             */
/*   Updated: 2016/04/29 11:25:04 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	background_color(char *color, t_env *rt)
{
	int i;

	i = 0;
	if (!color || ft_strlen(color) > 6)
		ft_exit("\033[31mBad format for background_color\n");
	while (color[i])
	{
		if (color[i] < '0' || (color[i] > '9' && color[i] < 'A')
				|| (color[i] > 'F' && color[i] < 'a') || color[i] > 'f')
			ft_exit("\033[31mBad format for background_color\n");
		i++;
	}
	rt->bg_color = ft_atoi_base(color, 16);
}

static void	objects(char *object, t_env *rt, int fd)
{
	if (!ft_strcmp(object, "camera"))
		parsing_camera(fd, rt);
	else if (!ft_strcmp(object, "light"))
		parsing_light(fd, rt);
	else if (!ft_strcmp(object, "sphere") ||
		!ft_strcmp(object, "plane") || !ft_strcmp(object, "cylinder") ||
		!ft_strcmp(object, "cone"))
		parsing_objects(fd, object, rt);
	else
		ft_exit("\033[31mA defined object was not found\n");
}

static void	resolution(float width, float height, t_env *rt)
{
	if (width < 7680 && width > 0)
		rt->w = width;
	else
		ft_exit("\033[31mWidth too large\n");
	if (height < 4320 && height > 0)
		rt->h = height;
	else
		ft_exit("\033[31mHeight too large\n");
}

static void	parsing(char **tab, t_env *rt, int fd)
{
	if (!ft_strcmp(tab[0], "background_color"))
		background_color(tab[2], rt);
	else if (!ft_strcmp(tab[0], "resolution"))
		(tab[2] && tab[3]) ? (resolution(ft_atof(tab[2]),
					ft_atof(tab[3]), rt)) :
			(ft_exit("\033[31mParameter missing for resolution\n"));
	else if (!ft_strcmp(tab[0], "object"))
		objects(tab[2], rt, fd);
	tab_free(tab);
}

void		global_parser(char *file, t_env *rt)
{
	int		fd;
	char	*line;
	char	**tab;

	init_all(file, rt);
	if ((fd = open(file, O_RDONLY)) == -1)
		ft_exit("\033[31mThis scene doesn't exist\n");
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0])
		{
			tab = ft_strsplit(line, ' ');
			parsing(tab, rt, fd);
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
	(close(fd) == -1) ? (ft_exit("\033[31mThis scene failed to close")) : (0);
}
