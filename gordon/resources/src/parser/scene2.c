/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grass-kw <grass-kw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/22 12:16:08 by grass-kw          #+#    #+#             */
/*   Updated: 2016/04/24 18:55:00 by grass-kw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_v1.h"

void	scene5_2(t_env *e)
{
	t_obj	cylindre;
	t_obj	cone;
	t_obj	spot;
	t_obj	plan2;

	spot.type = SPOT;
	spot.origin = set_coord(-2000, 600, 200);
	spot.color = set_rgb(255, 255, 255);
	cylindre.type = CYLINDRE;
	cylindre.origin = set_coord(0, 100, 0);
	cylindre.size = 30;
	cylindre.angle = set_coord(-0.75, 0.1, 0);
	cylindre.color = set_rgb(0, 255, 0);
	cone.type = CONE;
	cone.origin = set_coord(0, -65, 50);
	cone.angle = set_coord(0.55, 0, 0);
	cone.size = 100;
	cone.color = set_rgb(255, 255, 0);
	plan2.type = PLAN;
	plan2.origin = set_coord(0, 0, 1);
	plan2.color = set_rgb(255, 255, 255);
	ft_lstadd(&(e->list_obj), ft_lstnew(&(cylindre), sizeof(t_obj)));
	ft_lstadd(&(e->list_obj), ft_lstnew(&(cone), sizeof(t_obj)));
	ft_lstadd(&(e->list_obj), ft_lstnew(&(plan2), sizeof(t_obj)));
	ft_lstadd(&(e->list_spot), ft_lstnew(&(spot), sizeof(t_obj)));
}

void	scene5(t_env *e)
{
	t_obj	sphere1;
	t_obj	plan1;

	e->nb_spots = 1;
	e->camera.type = CAMERA;
	e->camera.angle = set_coord(0, 0, 0);
	e->camera.origin = set_coord(0, 0, 0);
	sphere1.type = SPHERE;
	sphere1.origin = set_coord(-15, -5, 45);
	sphere1.size = 55;
	sphere1.color = set_rgb(255, 0, 0);
	plan1.type = PLAN;
	plan1.origin = set_coord(1, 0, 0);
	plan1.size = -300;
	plan1.color = set_rgb(50, 50, 300);
	ft_lstadd(&(e->list_obj), ft_lstnew(&(sphere1), sizeof(t_obj)));
	ft_lstadd(&(e->list_obj), ft_lstnew(&(plan1), sizeof(t_obj)));
	scene5_2(e);
}

void	test(t_env *e)
{
	t_obj	sphere1;
	t_obj	sphere2;

	e->camera.type = CAMERA;
	e->camera.angle = set_coord(0, 0, 0);
	e->camera.origin = set_coord(-300, 0, 0);
	sphere1.type = PLAN;
	sphere1.origin = set_coord(0.08, 0.05, -1);
	sphere1.size = 200;
	sphere1.color = set_rgb(255, 0, 0);
	sphere2.type = CONE;
	sphere2.origin = set_coord(0, 0, 0);
	sphere2.size = 100;
	sphere2.color = set_rgb(0, 0, 255);
	ft_lstadd(&(e->list_obj), ft_lstnew(&sphere1, sizeof(t_obj)));
	ft_lstadd(&(e->list_obj), ft_lstnew(&sphere2, sizeof(t_obj)));
	print_lstobj(e->list_obj);
}
