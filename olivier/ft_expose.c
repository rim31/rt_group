/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expose.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <oseng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 18:39:15 by oseng             #+#    #+#             */
/*   Updated: 2016/04/22 11:51:45 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static	void	ft_intersection(t_env *a, int i)
{
	ft_calvect(a);
	if (ft_strcmp(a->obj[i].name, "plan") == 0)
		ft_plan(a, a->obj[i]);
	else if (ft_strcmp(a->obj[i].name, "sphere") == 0)
		ft_sphere(a, a->obj[i]);
	else if (ft_strcmp(a->obj[i].name, "cylindre") == 0)
		ft_cylind(a, a->obj[i]);
	else if (ft_strcmp(a->obj[i].name, "cone") == 0)
		ft_cone(a, a->obj[i]);
	else
		ft_error();
}

t_vect			ft_rot_cam(t_vect vect, t_env objet)
{
	double		tmp1;
	double		tmp2;

	tmp1 = vect.y;
	tmp2 = vect.z;
	vect.y = tmp1 * cos(objet.angle.x) - tmp2 * sin(objet.angle.x);
	vect.z = tmp1 * sin(objet.angle.x) + tmp2 * cos(objet.angle.x);
	tmp1 = vect.x;
	tmp2 = vect.z;
	vect.x = tmp1 * cos(objet.angle.y) + tmp2 * sin(objet.angle.y);
	vect.z = -tmp1 * sin(objet.angle.y) + tmp2 * cos(objet.angle.y);
	tmp1 = vect.x;
	tmp2 = vect.y;
	vect.x = tmp1 * cos(objet.angle.z) - tmp2 * sin(objet.angle.z);
	vect.y = tmp1 * sin(objet.angle.z) + tmp2 * cos(objet.angle.z);
	return (vect);
}

t_vect			ft_rot_cam_inv(t_vect vect, t_env objet)
{
	double		tmp1;
	double		tmp2;
	t_vect		angle;

	angle.x = -objet.angle.x;
	angle.y = -objet.angle.y;
	angle.z = -objet.angle.z;
	tmp1 = vect.y;
	tmp2 = vect.z;
	vect.y = tmp1 * cos(angle.x) - tmp2 * sin(angle.x);
	vect.z = tmp1 * sin(angle.x) + tmp2 * cos(angle.x);
	tmp1 = vect.x;
	tmp2 = vect.z;
	vect.x = tmp1 * cos(angle.y) + tmp2 * sin(angle.y);
	vect.z = -tmp1 * sin(angle.y) + tmp2 * cos(angle.y);
	tmp1 = vect.x;
	tmp2 = vect.y;
	vect.x = tmp1 * cos(angle.z) - tmp2 * sin(angle.z);
	vect.y = tmp1 * sin(angle.z) + tmp2 * cos(angle.z);
	return (vect);
}

t_env			ft_calvect(t_env *a)
{
	t_vect		init;
	t_vect		end;

	init.x = a->cam.x;
	init.y = a->cam.y;
	init.z = a->cam.z;
	end.x = 300 + a->yy;
	end.y = L / 2 - a->x - a->xx;
	end.z = H / 2 - a->y;
	a->ray.x = end.x - init.x;
	a->ray.y = end.y - init.y;
	a->ray.z = end.z - init.z;
	a->ray = ft_rot_cam(a->ray, *a);
	return (*a);
}

int				ft_expose(t_env *a)
{
	int			i;

	a->data = (char*)mlx_get_data_addr(a->image, &a->bpp, &a->size_line,
			&a->endian);
	a->y = -1;
	while (a->y++ < H)
	{
		a->x = -1;
		while (a->x++ < L)
		{
			i = 0;
			a->color = 0x000000;
			a->k0 = 1000000;
			while (i <= a->nbobjet)
			{
				ft_intersection(a, i);
				i++;
			}
			mlx_pixel_put_to_image(a->x, a->y, a);
		}
	}
	mlx_put_image_to_window(a->mlx, a->win, a->image, 0, 0);
	return (0);
}
