/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_camera_light.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 15:28:32 by svelhinh          #+#    #+#             */
/*   Updated: 2016/04/28 19:03:41 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	init_lights(t_env *rt)
{
	int i;

	i = 0;
	while (i < rt->nblight)
	{
		rt->light[i].center.x = 0;
		rt->light[i].center.y = 0;
		rt->light[i].center.z = 0;
		rt->light[i].color.r = 0;
		rt->light[i].color.g = 0;
		rt->light[i].color.b = 0;
		i++;
	}
}

void		count_light(t_env *rt, char *file)
{
	int		fd;
	char	*line;

	if ((fd = open(file, O_RDONLY)) == -1)
		ft_exit("\033[31mThis scene doesn't exist\n");
	while (get_next_line(fd, &line) > 0)
	{
		rt->nblight += (!ft_strcmp(line, "object : light")) ? (1) : (0);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	(close(fd) == -1) ? (ft_exit("\033[31mThis scene failed to close")) : (0);
	if (!(rt->light = (t_light *)malloc(sizeof(t_light) * rt->nblight)))
		ft_exit("malloc of rt->light failed in count_light");
	init_lights(rt);
}

void		init_camera(t_env *rt)
{
	rt->eye.x = 0;
	rt->eye.y = 0;
	rt->eye.z = 0;
	rt->cam_angle.x = 0;
	rt->cam_angle.y = 0;
	rt->cam_angle.z = 0;
}
