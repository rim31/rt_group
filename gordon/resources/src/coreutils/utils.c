/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grass-kw <grass-kw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/19 15:34:15 by grass-kw          #+#    #+#             */
/*   Updated: 2016/04/22 22:08:44 by grass-kw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_v1.h"

t_coor	set_coord(double x, double y, double z)
{
	t_coor pos;

	pos.x = x;
	pos.y = y;
	pos.z = z;
	return (pos);
}

t_color	set_rgb(int r, int g, int b)
{
	t_color rgb;

	(void)rgb;
	rgb.r = r;
	rgb.g = g;
	rgb.b = b;
	return (rgb);
}

void	print_color(t_color color)
{
	printf("r %d g %d b %d\n", color.r, color.g, color.b);
}

void	print_tab(t_coor tab)
{
	printf("tab[%lf, %lf, %lf]\n", tab.x, tab.y, tab.z);
}

void	print_obj(t_obj obj)
{
	printf("obj :\n");
	printf("type %d\n", obj.type);
	printf("color ");
	print_color(obj.color);
	printf("origin ");
	print_tab(obj.origin);
	printf("angle ");
	print_tab(obj.angle);
	printf("size %lf\n", obj.size);
}

void	print_elem(t_list *elem)
{
	t_obj	obj;

	obj = *((t_obj *)elem->content);
	print_obj(obj);
}

void	print_lstobj(t_list *lst)
{
	ft_lstiter(lst, print_elem);
}
