/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 11:57:50 by svelhinh          #+#    #+#             */
/*   Updated: 2016/04/27 12:49:22 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	mlx_pixel_put_to_image(int color, t_env *img, int x, int y)
{
	unsigned char	a;
	unsigned char	b;
	unsigned char	g;
	unsigned char	r;

	if (x < img->w && x > 0 && y < img->h && y > 0)
	{
		if (!img->endian)
		{
			b = (color & 0xFF000000) >> 24;
			r = (color & 0xFF00) >> 8;
		}
		else
		{
			r = (color & 0xFF000000) >> 24;
			b = (color & 0xFF00) >> 8;
		}
		g = (color & 0xFF0000) >> 16;
		a = (color & 0xFF);
		img->data[y * img->line + x * img->bpp / 8] = a;
		img->data[y * img->line + x * img->bpp / 8 + 1] = r;
		img->data[y * img->line + x * img->bpp / 8 + 2] = g;
		img->data[y * img->line + x * img->bpp / 8 + 3] = b;
	}
}

void	missing_parameter(char **line2)
{
	if (ft_strcmp(line2[1], ":"))
		ft_exit("\033[31mCharacter ':' not found\n");
	if (!line2[2] || !line2[3] || !line2[4])
		ft_exit("\033[31mMissing parameter\n");
}

void	check_color(double r, double g, double b)
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
