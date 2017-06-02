/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grass-kw <grass-kw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 11:57:50 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/12 17:24:27 by grass-kw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		tab_free(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		ft_strclean(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

void		mlx_pixel_put_to_image(int color, t_env *img, int x, int y)
{
	unsigned char	a;
	unsigned char	b;
	unsigned char	g;
	unsigned char	r;
	int				i;

	if (x < img->w && x > 0 && y < img->h && y > 0)
	{
		a = 0xff;
		r = (color & 0xFF0000) >> 16;
		g = (color & 0xFF00) >> 8;
		b = (color & 0xFF);
		i = y * img->line + x * img->bpp / 8;
		img->data[i] = r;
		img->data[i + 1] = g;
		img->data[i + 2] = b;
		img->data[i + 3] = a;
	}
}

void		missing_parameter(char **tab)
{
	if ((ft_strcmp(tab[0], "parallel") && (!tab[0] || !tab[1] || !tab[2] ||
		!tab[3] || !tab[4] || tab[5] || ft_strcmp(tab[1], ":")))
		|| (!ft_strcmp(tab[0], "parallel") && (!tab[2]
		|| tab[3])))
	{
		ft_putstr("\033[31mWrong option for an object light (pos : 0 0 0 / ");
		ft_putstr("color : [0-1] [0-1] [0-1]) or camera (pos : 0 0 0 / angle ");
		ft_exit(": 1 1 1)\n");
	}
}

void		check_color(double r, double g, double b)
{
	if (r < 0 || r > 1 || g < 0 || g > 1 || b < 0 || b > 1)
		ft_exit("\033[31mColor must be between 0 and 1\n");
}

t_vector	calcul_ptinter(t_vector eye, t_vector r, double t)
{
	t_vector	ptinter;

	ptinter.x = eye.x + r.x * t;
	ptinter.y = eye.y + r.y * t;
	ptinter.z = eye.z + r.z * t;
	return (ptinter);
}
