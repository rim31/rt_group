/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grass-kw <grass-kw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/22 23:54:29 by grass-kw          #+#    #+#             */
/*   Updated: 2016/04/24 19:29:45 by grass-kw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_v1.h"

static t_color	get_color_shade(int total_shade)
{
	t_color	color;
	int		gray;
	int		coef;
	int		gray_final;

	gray = 110;
	coef = total_shade * 4;
	gray_final = gray - coef;
	color = set_rgb(gray_final, gray_final, gray_final);
	return (color);
}

static int		intersection_obj_spot(t_env *e)
{
	t_list	*cursor;
	t_obj	*obj;
	double	result;

	cursor = e->list_obj;
	while (cursor)
	{
		obj = (t_obj *)cursor->content;
		result = intersection(obj, &(e->camera.origin), &(obj->l));
		if (result > ZERO)
			return (1);
		cursor = cursor->next;
	}
	return (0);
}

int			shadow(t_env *e, t_color *color)
{
	t_list	*cursor;
	t_obj	spot;
	int		total_shade;

	total_shade = 0;
	cursor = e->list_spot;
	while (cursor)
	{
		spot = *((t_obj *)cursor->content);
		total_shade += intersection_obj_spot(e);
		cursor = cursor->next;
	}
	if (total_shade > 0)
	{
		*color = get_color_shade(total_shade);
		return (1);
	}
	return (0);
}
