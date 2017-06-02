/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_pixel_put_to_image.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <oseng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 16:32:16 by oseng             #+#    #+#             */
/*   Updated: 2016/04/13 11:53:38 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void				mlx_pixel_put_to_image(int x, int y, t_env *e)
{
	unsigned char	a;
	unsigned char	b;
	unsigned char	g;
	unsigned char	r;

	b = (e->color & 0xFF000000) >> 24;
	g = (e->color & 0xFF0000) >> 16;
	r = (e->color & 0xFF00) >> 8;
	a = (e->color & 0xFF);
	if (y > 0 && x > 0 && x < L && y < H)
	{
		e->data[y * e->size_line + x * e->bpp / 8] = a;
		e->data[y * e->size_line + x * e->bpp / 8 + 1] = r;
		e->data[y * e->size_line + x * e->bpp / 8 + 2] = g;
		e->data[y * e->size_line + x * e->bpp / 8 + 3] = b;
	}
}
