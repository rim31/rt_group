/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 11:57:50 by svelhinh          #+#    #+#             */
/*   Updated: 2016/05/27 18:53:57 by svelhinh         ###   ########.fr       */
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

void		missing_parameter(char **tab)
{
	if (!tab[0] || !tab[1] || !tab[2] || !tab[3] || !tab[4] || tab[5] ||
		ft_strcmp(tab[1], ":"))
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

void	save(t_env *rt)
{
	int fd;
	unsigned int w = rt->w;
	unsigned int h = rt->h;
	unsigned int signature = 0x4d42;
	unsigned int padding = 0;

	if ((w * 3) % 4 != 0)
		padding = 4 - ((w * 3) % 4);

	unsigned int size_bmp = (w * 3 + padding) * h + 54;
	unsigned int reserved = 0;
	unsigned int offset_to_start = 54;
	unsigned int bitmap_info_header = 40;
	unsigned int planes = 1;
	unsigned int bpp = 24;
	unsigned int compression = 0;
	unsigned int size_img = (w * 3 + padding) * h;
	unsigned int horizontal_r = 1;
	unsigned int vertical_r = 1;
	unsigned int colors_img = 0;
	unsigned int colors_important = 0;

	if ((fd = open("scene.bmp", O_WRONLY | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO)) == -1)
		ft_exit("\033[31mFailed ot open scene.bmp");
	write(fd, &signature, 2);
	write(fd, &size_bmp, 4);
	write(fd, &reserved, 2);
	write(fd, &reserved, 2);
	write(fd, &offset_to_start, 4);
	write(fd, &bitmap_info_header, 4);
	write(fd, &w, 4);
	write(fd, &h, 4);
	write(fd, &planes, 2);
	write(fd, &bpp, 2);
	write(fd, &compression, 4);
	write(fd, &size_img, 4);
	write(fd, &horizontal_r, 4);
	write(fd, &vertical_r, 4);
	write(fd, &colors_img, 4);
	write(fd, &colors_important, 4);
	char *color;
	color = (char *)malloc(sizeof(char) * w * h * 3);
	for(int i = 0, j = 0; i < w * h * 4; i += 4, j += 3)
	{
		color[j] = rt->data[i];
		color[j + 1] = rt->data[i + 1];
		color[j + 2] = rt->data[i + 2];
	}
	int j = w * h * 3 - (w * 3);
	for(int i = 0; i < h; i++)
	{
		write(fd, &color[j], 3 * w);
		write(fd, 0, padding);
		j -= w * 3;
	}
	close(fd);
}



// unsigned int *image;
// write(fd, &image[1], 1000 * 3)
