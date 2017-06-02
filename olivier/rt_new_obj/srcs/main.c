/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <oseng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 11:08:19 by svelhinh          #+#    #+#             */
/*   Updated: 2016/05/05 11:00:02 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void init_mlx(t_env *rt)
{
	(!(rt->mlx = mlx_init())) ? (ft_exit("mlx_init() failed in main()")) : (0);
	if (!(rt->win = mlx_new_window(rt->mlx, rt->w, rt->h, "Raytracer")))
		ft_exit("mlx_new_window() in main() failed");
	mlx_string_put(rt->mlx, rt->win, 2, 2, 0xFFFFFF, "LOADING->->->");
	mlx_mouse_hook(rt->win, my_mouse_funct, rt);
	mlx_hook(rt->win, 2, (1L << 0), key_press, rt);
	mlx_hook(rt->win, 3, (1L << 1), key_release, rt);
	mlx_expose_hook(rt->win, expose, rt);
	// expose(rt);
	mlx_loop(rt->mlx);
}

void	ft_exit(char *s)
{
	ft_putstr_fd(s, 2);
	exit(0);
}

int		main(int ac, char **av)
{
	t_env rt;

	if (ac != 2)
		(ac > 2) ? (ft_exit("\033[31mToo many parameters\n")) :
			(ft_exit("\033[31mNot enough parameters\n"));
	if (av[1][ft_strlen(av[1]) - 3] == '.' && av[1][ft_strlen(av[1]) - 2] == 'r'
			&& av[1][ft_strlen(av[1]) - 1] == 't')
		global_parser(av[1], &rt);
	else
		ft_exit("\033[31mFiles must have .rt extension\n");
	(!(rt.mlx = mlx_init())) ? (ft_exit("mlx_init() failed in main()")) : (0);
	if (!(rt.win = mlx_new_window(rt.mlx, rt.w, rt.h, "Raytracer")))
		ft_exit("mlx_new_window() in main() failed");

	mlx_string_put(rt.mlx, rt.win, 2, 2, 0xFFFFFF, "LOADING...");
	// if (rt.menu == 1 && (rt.textur = mlx_xpm_file_to_image(rt.mlx, "img/mur.xpm",
	// 		&rt.pxlh, &rt.pxlw)))
	// 	mlx_put_image_to_window(rt.mlx, rt.win, rt.textur, 1, 1);

	mlx_mouse_hook(rt.win, my_mouse_funct, &rt);

	mlx_hook(rt.win, 2, (1L << 0), key_press, &rt);
	mlx_hook(rt.win, 3, (1L << 1), key_release, &rt);
	mlx_loop_hook(rt.mlx, expose, &rt);
	mlx_loop(rt.mlx);
	return (0);
}
