/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rims <rims@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 10:49:33 by svelhinh          #+#    #+#             */
/*   Updated: 2016/04/27 23:05:16 by rims             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "get_next_line.h"
// # include <mlx.h>
# include "../minilibx_macos/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# define UP 126 /*65362*/
# define DOWN 125 /*65364*/
# define LEFT 123 /*65361*/
# define RIGHT 124 /*65363*/
# define ESC 53 /*65307*/
# define SPEED 100
# define LIGHT 0
# define SPHERE 1
# define PLANE 2
# define CYLINDER 3
# define CONE 4

typedef struct	s_vector
{
	double		x;
	double		y;
	double		z;
}				t_vector;

typedef struct	s_color
{
	double		r;
	double		g;
	double		b;
}				t_color;

typedef struct	s_light
{
	t_vector	center;
	t_color		color;
}				t_light;

typedef struct	s_figure
{
	int			name;
	double		radius;
	t_vector	center;
	t_color		color;
	t_vector	angle;
}				t_figure;

typedef struct	s_env
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*data;
	int			bg_color;
	int			final_color;
	int			bpp;
	int			line;
	int			endian;
	int			keyup;
	int			keydown;
	int			keyleft;
	int			keyright;
	int			nbobj;
	int			nblight;
	double		t;
	double		w;
	double		h;
	double		xx;
	double		zz;
	t_color		color;
	t_figure	*object;
	t_vector	cam_angle;
	t_vector	eye;
	t_light		*light;
}				t_env;

void			raytracer(t_env *rt);
t_vector		rotations(t_vector vec, double x, double y, double z);


/*
**	-------------------	INITIALISATION	---------------------------
*/
void			init_camera(t_env *rt);
void			init_all(char *file, t_env *rt);
void			count_light(t_env *rt, char *file);
/*
**	-------------------------------------------------------
*/
/*
**	--------------------	PARSER	---------------------------
*/
void			global_parser(char *file, t_env *rt);
void			count_objects(t_env *rt, char *file);
void			parsing_camera(int fd, t_env *rt);
void			parsing_objects(int fd, char *object, t_env *rt);
void			parsing_light(int fd, t_env *rt);
/*
**	-------------------------------------------------------
*/
/*
**	-------------------	EVENTS	---------------------------
*/
int				expose(t_env *rt);
int				key_press(int keycode, t_env *rt);
int				key_release(int keycode, t_env *rt);
/*
**	-------------------------------------------------------
*/
/*
**	-------------------	OBJECTS	---------------------------
*/
int				sphere(t_vector r, t_figure s, double *t, t_vector eye);
int				plane(t_vector r, t_figure p, double *t, t_vector eye);
int				cylinder(t_vector r, t_figure cy, double *t, t_vector eye);
int				cone(t_vector r, t_figure co, double *t, t_vector eye);
/*
**	-------------------------------------------------------
*/
/*
**	-------------------	LIGHT	---------------------------
*/
void			light(t_env *rt, t_figure object, t_light light, t_vector inter);
/*
**	-------------------------------------------------------
*/
/*
**	-------------------	VECTORS	---------------------------
*/
t_vector		vecsub(t_vector *v1, t_vector *v2);
double			vecdot(t_vector *v1, t_vector *v2);
t_vector		normalize(t_vector *v1);
/*
**	-------------------------------------------------------
*/
/*
**	------------	OTHER	-----------------------
*/
void			ft_exit(char *s);
void			mlx_pixel_put_to_image(int color, t_env *img, int x, int y);
void			missing_parameter(char **line2);
void			check_color(double r, double g, double b);
t_vector		calcul_ptinter(t_vector eye, t_vector r, double t);
/*
**	-------------------------------------------------------
*/

#endif
