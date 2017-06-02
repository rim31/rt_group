/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grass-kw <grass-kw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 10:49:33 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/13 11:44:41 by grass-kw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "get_next_line.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <pthread.h>
# include <gtk/gtk.h>
# include <cairo.h>
# include <gsl/gsl_poly.h>
# define MAXREFLECTION 15
# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124
# define ESC 53
# define MENU 49
# define SAVE 1
# define SPEED 30
# define LIGHT 0
# define SPHERE 1
# define PLANE 2
# define CYLINDER 3
# define CONE 4
# define L_SPHERE 5
# define L_CYLINDER 6
# define L_CONE 7
# define TRIANGLE 8
# define QUADRILATERAL 9
# define HYPERBOL 10
# define CUBE 11
# define ELLIPSOIDE 12
# define TORUS 13
# define PARABOL 14
# define BRICKS 1
# define RANDOM 2
# define ATOF(a) (ft_atof(tab[a]))
# define THREADS 8

typedef struct			s_vector
{
	double				x;
	double				y;
	double				z;
}						t_vector;

typedef struct			s_color
{
	double				r;
	double				g;
	double				b;
}						t_color;

typedef struct			s_light
{
	t_vector			center;
	t_color				color;
	int					parallel;
}						t_light;

typedef struct			s_procedural
{
	int					active;
	double				scale;
	t_color				color1;
	t_color				color2;
}						t_procedural;

typedef struct			s_texture
{
	char				*path;
	int					height;
	int					width;
	int					row;
	double				scale;
	guchar				*buffer;
	gboolean			alpha;
}						t_texture;

typedef struct			s_material
{
	char				*name;
	double				specular;
	double				specular_power;
	int					shiny;
	double				reflection;
	int					transparent;
	double				refraction;
	double				i_refract;
	int					ripple;
	t_procedural		procedural;
	t_texture			texture;
}						t_material;

typedef struct			s_figure
{
	int					name;
	double				radius;
	double				separation;
	double				size;
	int					shadows;
	t_vector			a;
	t_vector			b;
	t_vector			c;
	t_vector			center;
	t_color				color;
	t_vector			angle;
	t_material			material;
}						t_figure;

typedef struct			s_gtk
{
	GtkWidget			*menubar;
	GtkWidget			*filemenu;
	GtkWidget			*file;
	GtkWidget			*open;
	GtkWidget			*save;
	GtkWidget			*quit;
	GtkWidget			*antialiasing;
	GtkWidget			*filters;
	GtkWidget			*chooser;
	GtkWidget			*area;
	GtkWidget			*box;
	GtkWidget			*cartoon;
}						t_gtk;

typedef struct			s_env
{
	double				start_h;
	double				end_h;
	GtkWidget			*win;
	GtkWidget			*load;
	GtkWidget			*l_win;
	GError				*error;
	GtkCssProvider		*provider;
	GdkDisplay			*display;
	GdkScreen			*screen;
	GtkWidget			*dialog;
	unsigned char		*tmp_data;
	t_gtk				gtk;
	int					i_gtk;
	char				*data;
	t_color				bg_color;
	int					final_color;
	int					bpp;
	int					line;
	int					endian;
	int					keyup;
	int					keydown;
	int					keyleft;
	int					keyright;
	int					nbobj;
	int					nblight;
	int					nbmat;
	double				t;
	double				w;
	double				h;
	double				xx;
	double				zz;
	double				angle;
	t_vector			inter;
	t_color				color;
	t_color				tmp_color;
	t_figure			*object;
	t_vector			cam_angle;
	t_vector			eye;
	t_light				*light;
	t_vector			tmp_l_center;
	t_vector			tmp_inter;
	t_vector			tmp_center;
	t_vector			tmp_rlight;
	t_vector			orig_reflect;
	t_color				color2;
	t_color				color3;
	double				ambient;
	t_vector			reflect;
	int					reflection;
	double				first_reflec;
	double				first_refrac;
	int					i2;
	int					i_obj;
	int					i_mat;
	int					i_light;
	int					disk_s;
	int					disk_cy;
	int					disk_co;
	int					max_reflect;
	int					max_refract;
	double				prev_refr;
	int					menu;
	int					rotcam;
	int					effect;
	int					endian1;
	int					bpp1;
	int					line1;
	int					pxlh;
	int					pxlw;
	int					filter;
	t_color				filter_color;
	int					antialiasing;
	int					cel_shading;
	t_material			*materials;
	gboolean			animation;
	GdkRGBA				filter_gtk;
	int					x_aliasing;
	int					y_aliasing;
	double				x;
	double				y;
	double				diffuse;

}						t_env;

void					*raytracer(void *args);
t_vector				rotations(t_vector vec, double x, double y, double z);
void					reflec_refrac(t_env *rt, t_vector ray, t_vector orig);
void					intersection(t_env *rt, t_vector ray, t_vector origin);
void					calcul_light(t_env *rt, int i2);
double					perlin(t_vector inter, double alpha, double beta,
	int n);
t_vector				normal_torus(t_vector i, t_figure to);
/*
**	----------------------------	GTK		------------------------
*/
void					gtk(t_env *rt);
gboolean				draw_area (GtkWidget *da, GdkEvent *event,
	gpointer data);
void					antialiasing_window(GtkWidget *button, gpointer data);
void					filters_window(GtkWidget *button, gpointer data);
void					open_file(GtkWidget *button, gpointer data);
void					cartoon_effect(GtkWidget *button, gpointer data);
void					screenshot(GtkWidget *button, gpointer data);
gchar					*format_value_callback(GtkScale *scale, gdouble value,
	gpointer data);
void					select_antialiasing(GtkWidget *button, gpointer data);
void					refresh_antialiasing(GtkRange *range, gpointer data);
void					antialiasing_window(GtkWidget *button, gpointer data);
/*
**	-------------------------------------------------------
*/
/*
**	-------------------	INITIALISATION	---------------------------
*/
void					init_camera(t_env *rt);
void					init_all(char *file, t_env *rt);
void					count_light(t_env *rt, char *file);
void					count_materials(t_env *rt, char *file);
void					count_objects(t_env *rt, char *file);
/*
**	-------------------------------------------------------
*/
/*
**	--------------------	PARSER	---------------------------
*/
void					global_parser(char *file, t_env *rt);
void					parsing_camera(int fd, t_env *rt);
void					parsing_objects(int fd, char *object, t_env *rt);
void					parsing_light(int fd, t_env *rt);
void					parsing_materials(int fd, char *material, t_env *rt);
void					init_name(t_env *rt, char *object);
void					background_color(char **color, t_env *rt);
void					objects(char *object, t_env *rt, int fd);
void					resolution(char **resolution, t_env *rt);
void					parsing_material(t_env *rt, t_material *materials,
	char *material);
void					missing_parameter_obj(char **tab);
/*
**	-------------------------------------------------------
*/
/*
**	-------------------	EVENTS	---------------------------
*/
int						expose(t_env *rt);
int						key_press(int keycode, t_env *rt);
int						key_release(int keycode, t_env *rt);
/*
**	-------------------------------------------------------
*/
/*
**	-------------------	OBJECTS	---------------------------
*/
int						sphere(t_vector r, t_figure s, double *t, t_vector eye);
int						plane(t_vector r, t_figure p, double *t, t_vector eye);
int						cylinder(t_vector r, t_figure cy, double *t,
	t_vector eye);
int						cone(t_vector r, t_figure cy, double *t, t_vector eye);
int						limited_sphere(t_vector r, t_figure s, t_vector eye,
	t_env *rt);
int						limited_cylinder(t_vector r, t_figure cy, t_vector eye,
	t_env *rt);
int						limited_cone(t_vector r, t_figure co, t_vector eye,
	t_env *rt);
double					distance_limit(double a, double b, double c);
int						disk_calcul(t_vector r, t_figure d, double *t,
	t_vector eye);
double					equation_s(t_vector *eye, t_vector *r, t_figure *s);
double					equation_cy(t_vector *eye, t_vector *r, t_figure *cy);
double					equation_co(t_vector *eye, t_vector *r, t_figure *co);
int						triangle(t_vector r, t_figure tri, double *t,
	t_vector eye);
int						quadrilateral(t_vector r, t_figure tri, double *t,
	t_vector eye);
int						cube(t_vector r, t_figure *cube, double *t,
	t_vector eye);
int						ellipsoide(t_vector r, t_figure s, double *t,
	t_vector eye);
int						torus(t_vector r, t_figure to, double *t,
	t_vector eye);
int						parabol(t_vector r, t_figure q, double *t,
	t_vector eye);
/*
**	-------------------------------------------------------
*/
/*
**	-------------------	REFELCTIONS & REFRACTIONS	------------------
*/
void					reflections(t_env *rt, t_vector ray, t_vector orig,
	int rr);
void					refractions(t_env *rt, t_vector ray, t_vector orig,
	int rr);
/*
**	-------------------------------------------------------
*/
/*
**	-------------------	LIGHT	---------------------------
*/
void					light(t_env *rt, t_figure object, t_light light);
int						shadows(t_env *rt, t_vector ray_light, t_vector inter);
double					specular_light(t_vector vecs[2], t_figure object,
	double ambient, int cel_shading);
t_vector				light_rotate(t_env *rt, t_figure object, t_light light);
void					color_light(t_env *rt, double spec, t_figure object,
	t_color light);
/*
**	-------------------------------------------------------
*/
/*
**	-------------------	VECTORS	---------------------------
*/
t_vector				vecadd(const t_vector *v1, const t_vector *v2);
t_vector				vecsub(const t_vector *v1, const t_vector *v2);
double					vecdot(const t_vector *v1, const t_vector *v2);
void					normalize(t_vector *v1);
void					vecscale(t_vector *v, const double factor);
t_vector				vecprod(const t_vector *v1, const t_vector *v2);
t_vector				new_vector(const double x, const double y,
	const double z);
t_vector				normal_torus(t_vector i, t_figure to);
t_vector				normale_parab(t_vector i);
/*
**	-------------------------------------------------------
*/
/*
**	------------	OTHER	-----------------------
*/
void					ft_exit(char *s);
void					mlx_pixel_put_to_image(int color, t_env *img, int x,
	int y);
void					missing_parameter(char **tab);
void					check_color(double r, double g, double b);
t_vector				calcul_ptinter(t_vector eye, t_vector r, double t);
void					render(t_env *rt);
void					tab_free(char **tab);
void					create_window(char *s);
int						my_mouse_funct(int button, int x, int y, t_env *rt);
t_color					color_filter(t_color color, t_color filter);
t_color					**create_aliasing_tab(t_env *rt, int aliasing);
void					aliasing_render(t_color **aliasing_tab, t_env *rt,
	double y);
void					free_aliasing_tab(t_color **aliasing_tab, t_env *rt,
	int aliasing);
t_figure				*add_figure(t_figure *objects, t_figure object,
	size_t n);
t_color					new_color(const double r, const double g,
	const double b);
/*
**	-------------------------------------------------------
*/
/*
**  ---------------  TEXTURES  ------------------------------
*/
t_color					textures(guchar *buffer, t_figure object,
	t_vector inter);
t_color					procedural(t_figure object, double u,
	double v);
/*
**  -------------------------------------------------------
*/
#endif
