/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <oseng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 17:50:12 by oseng             #+#    #+#             */
/*   Updated: 2016/04/22 11:15:07 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include "./libft/libft.h"
# include "./minilibx_macos/mlx.h"
# include <math.h>
# include <stdio.h>
# define H 1000
# define L 1000
# define RGB(r, g, b)(256 * 256 * (int)(r) + 256 * (int)(g) + (int)(b))

typedef struct	s_vect
{
	double		x;
	double		y;
	double		z;
}				t_vect;

typedef struct	s_obj
{
	char		*name;
	t_vect		center;
	t_vect		normale;
	t_vect		angle;
	double		d;
	t_vect		color;
	double		rayon;
	double		hauteur;
}				t_obj;

typedef struct	s_env
{
	void		*mlx;
	void		*win;
	void		*image;
	char		*data;
	int			color;
	int			bpp;
	int			size_line;
	int			endian;
	int			nbobjet;
	int			nblum;
	double		k;
	double		k0;
	double		cos_lum;
	int			x;
	int			y;
	int			xx;
	int			yy;
	int			keyup;
	int			keydown;
	int			keyleft;
	int			keyrigth;
	int			pas;
	t_vect		kk;
	t_vect		pt;
	t_vect		cam;
	t_vect		angle;
	t_vect		ray;
	t_obj		*obj;
	t_obj		*sphere;
	t_obj		*plan;
	t_obj		*cylind;
	t_obj		*cone;
	t_vect		*lum;
}				t_env;

void			ft_start_screen(t_env a);
void			mlx_pixel_put_to_image(int x, int y, t_env *e);
int				my_keyrelease_funct(int keyrelease, t_env *a);
int				my_key_funct(int keypress, t_env *a);
void			ft_error(void);
int				ft_expose(t_env *a);
t_env			ft_calvect(t_env *a);
int				ft_disc(t_env *a, double aa, double bb, double cc);
int				ft_plan(t_env *a, t_obj plan);
int				ft_sphere(t_env *a, t_obj sphere);
int				ft_cylind(t_env *a, t_obj cylind);
int				ft_cone(t_env *a, t_obj cone);
int				ft_ligth(double cos_lum, t_obj color, t_env *a);
void			ft_shadow(t_env *a, t_vect ray, t_vect pt);
t_vect			ft_rot(t_vect vect, t_obj objet);
t_vect			ft_rot_inv(t_vect vect, t_obj objet);
t_vect			ft_rot_cam(t_vect vect, t_env objet);
t_vect			ft_rot_cam_inv(t_vect vect, t_env objet);
t_vect			ft_norm(t_vect vect);
t_vect			ft_tmp(t_vect vect);
t_env			ft_init_scene(t_env *a, int i);
void			ft_scene_1(t_env *a);
void			ft_scene_2(t_env *a);
void			ft_scene_3(t_env *a);
void			ft_scene_4(t_env *a);
void			ft_scene_5(t_env *a);
void			ft_scene_6(t_env *a);
void			ft_scene_6bis(t_env *a);

#endif
