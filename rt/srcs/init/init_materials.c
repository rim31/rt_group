/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_materials.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 15:28:12 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/12 10:18:21 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	init_materials(t_env *rt)
{
	int i;

	i = 0;
	while (i < rt->nbmat)
	{
		ft_bzero(&(rt->materials[i]), sizeof(t_material));
		rt->materials[i].name = "nope";
		rt->materials[i].procedural.active = 0;
		rt->materials[i].procedural.scale = 0;
		rt->materials[i].procedural.color1 = new_color(0, 0, 0);
		rt->materials[i].procedural.color2 = new_color(0, 0, 0);
		rt->materials[i].texture.path = "\0";
		i++;
	}
}

void		count_materials(t_env *rt, char *file)
{
	int		fd;
	char	*line;
	int		tmp;

	if ((fd = open(file, O_RDONLY)) == -1)
		ft_exit("\033[31mThis scene doesn't exist\n");
	tmp = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (!ft_strcmp(ft_strsub(line, 0, ft_strlen("material_type")),
		"material_type"))
		{
			rt->nbmat++;
			tmp = (!tmp) ? (1) : (tmp);
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
	(close(fd) == -1) ? (ft_exit("\033[31mThis scene failed to close")) : (0);
	if (!tmp)
		rt->nbmat = 1;
	if (!(rt->materials = (t_material *)malloc(sizeof(t_material) * rt->nbmat)))
		ft_exit("malloc of rt->materials failed in count_materials");
	init_materials(rt);
}
