/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grass-kw <grass-kw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/10 07:08:20 by grass-kw          #+#    #+#             */
/*   Updated: 2016/04/22 12:33:09 by grass-kw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_v1.h"

void		env_setup(t_env *e)
{
	if ((e->mlx = mlx_init()) == NULL)
	{
		ft_putendl("fail to connect with X-server");
		exit(1);
	}
	if ((e->win = mlx_new_window(e->mlx, LENGHT, WIDTH, "rt_v1")) == NULL)
	{
		ft_putendl("fail to created window");
		exit(1);
	}
	if ((e->img = mlx_new_image(e->mlx, LENGHT, WIDTH)) == NULL)
	{
		ft_putendl("fail to created an image");
		exit(1);
	}
	if ((e->data = mlx_get_data_addr(e->img, &(e->bits_per_pixel)
		, &(e->size_line), &(e->endian))) == NULL)
	{
		ft_putendl("fail to obtain information frow image");
		exit(1);
	}
}
