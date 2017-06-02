/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <oseng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 10:49:33 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/02 14:50:34 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "get_next_line.h"
# include <mlx.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <pthread.h>
# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/cl.h>
# endif
# define MAXREFLECTION 15
# define UP 126 /*65362*/
# define DOWN 125 /*65364*/
# define LEFT 123 /*65361*/
# define RIGHT 124 /*65363*/
# define ESC 53 /*65307*/
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
# define QUADRIC 11
# define TORUS 12
# define OPENCL 0

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
}						t_light;

typedef struct			s_material
{
	double				specular;
	double				specular_power;
	int					shiny;
	double				reflection;
	int					transparent;
	double				refraction;
	double				i_refract;
}						t_material;

typedef struct			s_figure
{
	int					name;
	double				radius;
	double				separation;
	double				size;
	int					negativ;
	t_vector			a;
	t_vector			b;
	t_vector			c;
	t_vector			d;
	t_vector			center;
	t_color				color;
	t_vector			angle;
	t_material			material;
}						t_figure;

typedef struct			s_opencl
{
	cl_platform_id		platform_id;
	cl_device_id		device_id;
	cl_context			context;
	cl_command_queue	commands;
	cl_program			program;
	cl_kernel			kernel;
	cl_mem				image;
}						t_opencl;

typedef struct			s_env
{
	void				*mlx;
	void				*win;
	void				*img;
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
	int					start_h;
	int					end_h;
	t_vector			tmp_l_center;
	t_vector			tmp_inter;
	t_vector			tmp_center;
	t_vector			tmp_rlight;
	t_vector			orig_reflect;
	t_color				color2;
	double				ambient;
	t_vector			reflect;
	int					reflection;
	double				first_reflec;
	double				first_refrac;
	int					i2;
	int					i_obj;
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
	void				*wall;
	void				*textur;
	char				*data1;
	int					endian1;
	int					bpp1;
	int					line1;
	int					pxlh;
	int					pxlw;
	t_opencl			cl;
}						t_env;

void					*raytracer(void *arg);
t_vector				rotations(t_vector vec, double x, double y, double z);
void					reflec_refrac(t_env *rt, t_vector ray, t_vector orig);
void					intersection(t_env *rt, t_vector ray, t_vector origin);
void					calcul_light(t_env *rt, int i2, t_vector ray);
void					save(t_env *rt);
double					perlin(t_vector inter, double alpha, double beta, int n);
// float perlin(float x, float y, float res);

/*
**	-------------------	INITIALISATION	---------------------------
*/
void					init_camera(t_env *rt);
void					init_all(char *file, t_env *rt);
void					count_light(t_env *rt, char *file);
/*
**	-------------------------------------------------------
*/
/*
**	--------------------	PARSER	---------------------------
*/
void					global_parser(char *file, t_env *rt);
void					count_objects(t_env *rt, char *file);
void					parsing_camera(int fd, t_env *rt);
void					parsing_objects(int fd, char *object, t_env *rt);
void					parsing_light(int fd, t_env *rt);
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
int						cylinder(t_vector r, t_figure cy, double *t, t_vector eye, t_env *rt);
int						cone(t_vector r, t_figure co, double *t, t_vector eye);
int						limited_sphere(t_vector r, t_figure s, double *t, t_vector eye, int *disk);
int						limited_cylinder(t_vector r, t_figure cy, double *t, t_vector eye, int *disk);
int						limited_cone(t_vector r, t_figure co, double *t, t_vector eye, int *disk);
int						triangle(t_vector r, t_figure tri, double *t, t_vector eye);
int						quadrilateral(t_vector r, t_figure tri, double *t, t_vector eye);
int						quadric(t_vector r, t_figure s, double *t, t_vector eye);//quadric <===================================
int						torus(t_vector r, t_figure to, double *t, t_vector eye);//torus <===================================

/*
**	-------------------------------------------------------
*/
/*
**	-------------------	LIGHT	---------------------------
*/
void					light(t_env *rt, t_figure object, t_light light, t_vector ray);
/*
**	-------------------------------------------------------
*/
/*
**	-------------------	VECTORS	---------------------------
*/
t_vector				vecsub(t_vector *v1, t_vector *v2);
double					vecdot(t_vector *v1, t_vector *v2);
t_vector				normalize(t_vector *v1);
t_vector				vecadd(t_vector *v1, t_vector *v2);
t_vector				vecscale(t_vector *v, double factor);
t_vector				vecprod(t_vector *v1, t_vector *v2);
/*
**	-------------------------------------------------------
*/
/*
**	------------	OTHER	-----------------------
*/
void					ft_exit(char *s);
void					mlx_pixel_put_to_image(int color, t_env *img, int x, int y);
void					missing_parameter(char **tab);
void					check_color(double r, double g, double b);
t_vector				calcul_ptinter(t_vector eye, t_vector r, double t);
void					render(t_env *rt);
void					tab_free(char **tab);
void					create_window(char *s);
void					menu(t_env *rt);
int						my_mouse_funct(int button, int x, int y, t_env *rt);
/*
**	-------------------------------------------------------
*/
/*
**  ---------------  OPENCL  ------------------------------
*/
void					ft_opencl(t_env *rt);
void					opencl_setup(t_opencl *cl, int height, int width);
char					*read_file(char *path);
void					cl_init(t_opencl *cl, char *source);
void					cl_free(t_opencl *cl);
/*
**  -------------------------------------------------------
*/
#endif
