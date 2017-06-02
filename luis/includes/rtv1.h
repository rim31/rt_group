/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/05 14:51:08 by lnieto-m          #+#    #+#             */
/*   Updated: 2016/04/20 17:57:02 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "get_next_line.h"
# include <mlx.h>
# include <math.h>
# define WIDTH 1000
# define HEIGHT 650
# define RGB(r, g, b)(256 * 256 * (int)(r) + 256 * (int)(g) + (int)(b))

typedef struct	s_point
{
	int			x;
	int			y;
	int			z;
}				t_point;

typedef struct	s_vector
{
	double		x;
	double		y;
	double		z;
}				t_vector;

typedef struct	s_figure
{
	t_vector	center;
	double		rayon;
	double		hauteur;
	t_vector	normale;
	double		d;
	t_point		color;
	t_vector	rotation;
}				t_figure;

typedef struct	s_env
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*data;
	char		*av;
	int			color;
	int			bpp;
	int			line;
	int			endian;
	double		k;
	t_vector	eye;
	t_vector	rot_cam;
	t_figure	sphere;
	t_figure	sphere1;
	t_figure	sphere2;
	t_figure	sphere3;
	t_figure	sphere4;
	t_figure	sphere5;
	t_figure	sphere6;
	t_figure	sphere7;
	t_figure	sphere8;
	t_figure	plan1;
	t_figure	plan2;
	t_figure	plan3;
	t_figure	cylindre;
	t_figure	cylindre2;
	t_figure	cylindre3;
	t_figure	cylindre4;
	t_figure	cone;
	t_vector	spot1;
}				t_env;

int				key_p(int keycode);
int				expose_hook(t_env *e);
t_vector		rays(t_point p);
void			mlx_pixel_put_to_image(int x, int y, t_env *e);
t_vector		rotation(t_vector vision, t_vector angles);
t_vector		derotation(t_vector vision, t_vector angles);
int				solution(t_env *e, t_vector equ, double *solution);

/*
** tracé de forme -> raytrace.c
*/

void			sphere(t_vector vision, t_env *e, t_figure sphere,
				int(fct)(t_env *, t_vector));
void			plan(t_vector vision, t_env *e, t_figure plan,
				int(fct)(t_env *, t_vector));
void			cylindre(t_vector vision, t_env *e, t_figure cylindre,
				int(fct)(t_env *, t_vector));
void			cone(t_vector vision, t_env *e, t_figure cone,
				int(fct)(t_env *, t_vector));

/*
** ombres
*/

int				big_shadow(t_env *e, t_vector inter);
int				shadow(t_env *e, t_vector inter);
int				shadow2(t_env *e, t_vector inter);
int				s_shadow(t_vector inter, t_env *e, t_figure sphere);
int				cy_shadow(t_vector inter, t_env *e, t_figure cylindre);
int				co_shadow(t_vector inter, t_env *e, t_figure cone);

/*
** initialisation des scenes
*/

void			init0(t_env *e);
void			init1(t_env *e);
void			init2(t_env *e);
void			init3(t_env *e);
void			init4(t_env *e);
void			init5(t_env *e);
void			big_init(t_env *e);
void			big_init6(t_env *e);

/*
** balayage de l'ecran en fonction des objets presents
*/

void			balayage1(t_env *e);
void			balayage2(t_env *e);
void			balayage3(t_env *e);
void			balayage4(t_env *e);
void			balayage5(t_env *e);
void			big_balayage(t_env *e);

#endif
