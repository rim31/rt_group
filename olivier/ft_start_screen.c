/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_screen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <oseng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 18:42:23 by oseng             #+#    #+#             */
/*   Updated: 2016/04/20 14:11:14 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_error(void)
{
	ft_putendl("ERROR :-P");
	exit(0);
}

void	ft_start_screen(t_env a)
{
	if (a.x > L || a.x < 0 || a.y > H || a.y < 0 || H < 1 || L < 1)
		ft_error();
	a.mlx = mlx_init();
	a.win = mlx_new_window(a.mlx, L, H, "mlx 42");
	a.image = mlx_new_image(a.mlx, L, H);
	mlx_hook(a.win, 2, (1L << 0), my_key_funct, &a);
	mlx_hook(a.win, 3, (1L << 1), my_keyrelease_funct, &a);
	ft_expose(&a);
	mlx_loop(a.mlx);
}
