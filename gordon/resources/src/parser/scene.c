/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grass-kw <grass-kw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/22 12:15:16 by grass-kw          #+#    #+#             */
/*   Updated: 2016/04/24 19:48:36 by grass-kw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_v1.h"

void		scene1(t_env *e)
{
	t_obj	cone;
	t_obj	plan;
	t_obj	spot;

	e->camera.angle = set_coord(0, 0, 0);
	e->camera.origin = set_coord(-500, 0, 100);
	spot.type = SPOT;
	spot.origin = set_coord(-500, -200, 200);
	spot.color = set_rgb(255, 255, 255);
	e->nb_spots = 1;
	cone.type = CONE;
	cone.origin = set_coord(0, 0, 50);
	cone.angle = set_coord(0, 0, 0);
	cone.color = set_rgb(255, 0, 255);
	cone.size = 10;
	plan.type = PLAN;
	plan.origin = set_coord(0, 0, 1);
	plan.angle = set_coord(0, 0, 0);
	plan.color = set_rgb(50, 50, 255);
	plan.size = 1;
	ft_lstadd(&(e->list_obj), ft_lstnew(&(cone), sizeof(t_obj)));
	ft_lstadd(&(e->list_obj), ft_lstnew(&(plan), sizeof(t_obj)));
	ft_lstadd(&(e->list_spot), ft_lstnew(&(spot), sizeof(t_obj)));
}

void		scene2(t_env *e)
{
	t_obj	cylindre;

	e->nb_spots = 0;
	e->camera.angle = set_coord(0, 0, 0);
	e->camera.origin = set_coord(-500, 0, 0);
	cylindre.type = CYLINDRE;
	cylindre.origin = set_coord(0, 0, 0);
	cylindre.size = 100;
	cylindre.angle = set_coord(0, 0, 0);
	cylindre.color = set_rgb(0, 0, 255);
	ft_lstadd(&(e->list_obj), ft_lstnew(&(cylindre), sizeof(t_obj)));
}

void		scene3(t_env *e)
{
	t_obj	spot;
	t_obj	sphere1;

	e->camera.angle = set_coord(0, 0, 0);
	e->camera.origin = set_coord(0, 0, 0);
	spot.type = SPOT;
	spot.color = set_rgb(255, 255, 255);
	spot.origin = set_coord(-500, -300, 0);
	e->nb_spots = 1;
	sphere1.type = SPHERE;
	sphere1.origin = set_coord(0, 0, 0);
	sphere1.size = 100;
	sphere1.origin = set_coord(0, 0, 0);
	ft_lstadd(&(e->list_obj), ft_lstnew(&(sphere1), sizeof(t_obj)));
}

static void	scene4_2(t_env *e)
{
	t_obj	cone;
	t_obj	cylindre;
	t_obj	spot;

	spot.type = SPOT;
	spot.origin = set_coord(-2000, -600, 200);
	spot.color = set_rgb(255, 255, 255);
	e->nb_spots = 1;
	cylindre.type = CYLINDRE;
	cylindre.origin = set_coord(0, 100, 0);
	cylindre.angle = set_coord(-0.75, 0.1, 0);
	cylindre.size = 30;
	cylindre.color = set_rgb(0, 255, 0);
	cylindre.shine = 0.2;
	cone.type = CONE;
	cone.origin = set_coord(0, -65, 50);
	cone.angle = set_coord(0.55, 0, 0);
	cone.color = set_rgb(255, 255, 0);
	cone.size = 10;
	cone.shine = 1;
	ft_lstadd(&(e->list_spot), ft_lstnew(&(spot), sizeof(t_obj)));
	ft_lstadd(&(e->list_obj), ft_lstnew(&(cylindre), sizeof(t_obj)));
	ft_lstadd(&(e->list_obj), ft_lstnew(&(cone), sizeof(t_obj)));
}

void		scene4(t_env *e)
{
	t_obj	sphere1;
	t_obj	plan1;
	t_obj	plan2;

	e->camera.angle = set_coord(0, 0.45, 0.7);
	e->camera.origin = set_coord(-200, -300, 250);
	sphere1.type = SPHERE;
	sphere1.origin = set_coord(-15, -5, 45);
	sphere1.angle = set_coord(0, 0, 0);
	sphere1.size = 55;
	sphere1.color = set_rgb(255, 0, 0);
	sphere1.shine = 0.2;
	plan1.type = PLAN;
	plan1.origin = set_coord(1, 0, 0);
	plan1.angle = set_coord(0, 0, 0);
	plan1.size = -300;
	plan1.color = set_rgb(50, 50, 255);
	plan1.shine = 0.5
	plan2.type = PLAN;
	plan2.origin = set_coord(0, 0, 1);
	plan2.angle = set_coord(0, 0, 0);
	plan2.color = set_rgb(255, 255, 255);
	plan2.size = 0;
	plan2.shine = 0.2;
	ft_lstadd(&(e->list_obj), ft_lstnew(&(sphere1), sizeof(t_obj)));
	ft_lstadd(&(e->list_obj), ft_lstnew(&(plan1), sizeof(t_obj)));
	ft_lstadd(&(e->list_obj), ft_lstnew(&(plan2), sizeof(t_obj)));
	scene4_2(e);
}
