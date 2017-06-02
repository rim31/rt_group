/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_v1.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grass-kw <grass-kw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/10 06:21:56 by grass-kw          #+#    #+#             */
/*   Updated: 2016/04/24 19:32:06 by grass-kw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_V1_H
# define RT_V1_H
# include "libft.h"
# include "mlx.h"
# include "ft_keycode.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>
# define LENGHT 480
# define WIDTH 360
# define CAMERA 1
# define SPHERE 2
# define PLAN 3
# define CYLINDRE 4
# define CONE 5
# define SPOT 6
# define ZERO 0.001

typedef struct			s_color
{
	int					r;
	int					g;
	int					b;
}						t_color;

typedef	struct			s_coor
{
	double				x;
	double				y;
	double				z;
}						t_coor;

typedef struct			s_obj
{
	int					type;
	t_coor				origin;
	t_color				color;
	t_coor				angle;
	double				size;
	t_coor				l;
	double				shine;
}						t_obj;

typedef	struct			s_env
{
	void				*mlx;
	void				*win;
	void				*img;
	char				*data;
	int					bits_per_pixel;
	int					size_line;
	int					endian;
	t_coor				v;
	t_obj				camera;
	char				inter : 1;
	double				k;
	t_list				*list_obj;
	t_list				*list_spot;
	t_obj				*obj_inter;
	t_coor				*parametric_vector;
	t_coor				*n;
	double				norme;
	t_coor				dot_product;
	int					nb_spots;
}						t_env;

/*
** coreutils
*/
t_coor					set_coord(double x, double y, double z);
t_color					set_rgb(int r, int g, int b);
void					print_color(t_color color);
void					print_tab(t_coor tab);
void					print_obj(t_obj obj);
void					print_lstobj(t_list *lst);
void					valid_rgb(t_color *color);

/*
** mlx
*/
int						expose(t_env *e);
int						key(int key, t_env *e);
void					env_setup(t_env *e);
void					set_pixel(t_env *e, int color, int x, int y);
int						new_color(t_color rgb);
void					draw(t_env *e);

/*
*** raytracer
*/
t_color					raytracer(t_env *e, int i, int j);
void					rotation_inverse(t_coor *a, t_coor angle);
void					rotation(t_coor *a, t_coor angle);
double					sphere(t_obj *obj, t_coor *origin, t_coor *v);
double					plan(t_obj *obj, t_coor *origin, t_coor *v);
double					cylindre(t_obj *obj, t_coor *origin, t_coor *v);
double					cone(t_obj *obj, t_coor *origin, t_coor *v);
double					resolve(double delta, double a, double b);
double					intersection(t_obj *obj, t_coor *camera, t_coor *v);
int						shadow(t_env *e, t_color *color);
t_color					raytracing_obj(t_env *e, int i, int j);
t_color					brightness(t_env *e, t_color color);

/*
** parser
*/
void					parser(t_env *e, char *argument);
void					error(void);
void					scene1(t_env *e);
void					scene2(t_env *e);
void					scene3(t_env *e);
void					scene4(t_env *e);
void					scene5(t_env *e);
void					test(t_env *e);

#endif
