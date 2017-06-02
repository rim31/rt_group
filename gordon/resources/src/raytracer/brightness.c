/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brightness.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grass-kw <grass-kw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 19:11:22 by grass-kw          #+#    #+#             */
/*   Updated: 2016/04/24 19:44:33 by grass-kw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_v1.h"

static void		normalize_cylindre_cone(t_env *e, t_coor *n)
{
	if (e->obj_inter->type == CYLINDRE)
	{
		rotation(&(e->obj_inter->origin), e->obj_inter->angle);
		n->x = e->parametric_vector->x - e->obj_inter->origin.x;
		n->y = e->parametric_vector->y - e->obj_inter->origin.y;
		n->z = e->parametric_vector->z;
		rotation_inverse(&(e->obj_inter->origin), e->obj_inter->angle);
	}
	if (e->obj_inter->type == CONE)
	{
		rotation(&(e->obj_inter->origin), e->obj_inter->angle);
		n->x = e->parametric_vector->x - e->obj_inter->origin.x;
		n->y = e->parametric_vector->y - e->obj_inter->origin.y;
		n->z = e->parametric_vector->z + e->obj_inter->origin.z;
		rotation_inverse(&(e->obj_inter->origin), e->obj_inter->angle);
	}
}

static t_coor	normalize_obj(t_env *e)
{
	t_coor	n;

	if (e->obj_inter->type == SPHERE)
	{
		n.x = e->parametric_vector->x - e->obj_inter->origin.x;
		n.y = e->parametric_vector->y - e->obj_inter->origin.y;
		n.z = e->parametric_vector->z - e->obj_inter->origin.z;
	}
	if (e->obj_inter->type == PLAN)
	{
		n.x = e->parametric_vector->x - e->obj_inter->origin.x;
		n.y = e->parametric_vector->y - e->obj_inter->origin.y;
		n.z = e->parametric_vector->z - e->obj_inter->origin.z;
	}
	normalize_cylindre_cone(e, &n);
	return (n);
}

static t_color		assign_rgb(t_color new_color, t_env *e)
{
	t_color	color_final;

	color_final.r = new_color.r / e->nb_spots;
	color_final.g = new_color.g / e->nb_spots;
	color_final.b = new_color.b / e->nb_spots;
	return (color_final);
}

t_color			brightness(t_env *e, t_color color)
{
	t_list	*cursor;
	t_obj	*spot;
	t_color	new_color;

	*(e->n) = normalize_obj(e);
	new_color = set_rgb(0, 0, 0);
	cursor = e->list_spot;
	while (cursor)
	{
		spot = (t_obj *)cursor->content;
		e->dot_product = set_coord(e->n->x * spot->l.x, e->n->y * spot->l.y,
			e->n->z * spot->l.z);
		e->norme = sqrt(pow(e->dot_product.x, 2) +
			pow(e->dot_product.y, 2) + pow(e->dot_product.z, 2));
		new_color.r += color.r * e->obj_inter->shine * spot->color.r *
			cos(e->norme);
		new_color.g += color.g * e->obj_inter->shine * spot->color.g *
			cos(e->norme);
		new_color.b += color.b * e->obj_inter->shine * spot->color.b *
			cos(e->norme);
		cursor = cursor->next;
	}
	color = assign_rgb(new_color, e);
	return (color);
}
