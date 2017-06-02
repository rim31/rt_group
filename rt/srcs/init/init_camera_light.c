/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_camera_light.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grass-kw <grass-kw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 15:28:32 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/12 17:20:44 by grass-kw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		init_lights(t_env *rt)
{
	int i;

	i = 0;
	while (i < rt->nblight)
	{
		ft_bzero(&rt->light[i], sizeof(t_light));
		rt->light[i].center.z = -200;
		i++;
	}
}

static void		increment_tmp(t_env *rt, int *tmp)
{
	*tmp += 1;
	rt->nblight = 0;
}

void			count_light(t_env *rt, char *file)
{
	int		fd;
	char	*line;
	int		tmp;

	if ((fd = open(file, O_RDONLY)) == -1)
		ft_exit("\033[31mThis scene doesn't exist\n");
	tmp = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (!ft_strcmp(line, "object : light"))
		{
			rt->nblight++;
			tmp = (!tmp) ? (1) : (tmp);
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
	(close(fd) == -1) ? (ft_exit("\033[31mThis scene failed to close")) : (0);
	if (!tmp)
		increment_tmp(rt, &tmp);
	if (!(rt->light = (t_light *)malloc(sizeof(t_light) * rt->nblight)))
		ft_exit("malloc of rt->light failed in count_light");
	init_lights(rt);
}

void			init_camera(t_env *rt)
{
	rt->eye.x = 0;
	rt->eye.y = 0;
	rt->eye.z = -200;
	rt->cam_angle.x = 0;
	rt->cam_angle.y = 0;
	rt->cam_angle.z = 0;
}
