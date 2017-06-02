/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <oseng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 11:09:01 by rims              #+#    #+#             */
/*   Updated: 2016/05/03 17:15:19 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vector    texture(int keycode)
{
    t_vector color;

    if (keycode == 49)
    {
        if ((fd = open("scenes/scence_test.rt", O_RDONLY)) == -1)
            exit(0);
        if (!(rt->wall = mlx_xpm_file_to_image(rt->mlx, "img/mur.xpm",
            &rt->pxlh3, &rt->pxlw3)))
            ft_error();

rt->data1 = (unsigned char*)mlx_get_data_addr(rt->wall, &rt->bpp2,
	&rt->size_line2, &rt->endian2);

if (rt->small == 1)
	mlx_put_image_to_window(rt->mlx, rt->win, rt->texture,
		(int)(rt->width / 2 - 66 / 2), rt->higth - 89);
     return(color);
}


if (rt->menu == 1 && (rt->textur = mlx_xpm_file_to_image(rt->mlx, "img/mur.xpm",
		&rt->pxlh, &rt->pxlw)))
	mlx_put_image_to_window(rt->mlx, rt->win, rt->textur, 1, 1);
