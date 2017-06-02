/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/05 14:53:55 by lnieto-m          #+#    #+#             */
/*   Updated: 2016/04/21 17:08:36 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_usage(void)
{
	ft_putendl("Usage : ./rtv1 [1 <-> 7]");
	ft_putendl("1 - Cone, sphere, cylindre, 2 plans et spot");
	ft_putendl("2 - Scene 1 avec un different point de vue");
	ft_putendl("3 - Plan, cone et spot");
	ft_putendl("4 - Cylindre et spot");
	ft_putendl("5 - Sphere et spot");
	ft_putendl("6 - 4 cylindres, 8 spheres, 3 plans et un spot");
	ft_putendl("7 - 3 spheres, 2 plans, cylindre, cone et spot");
	exit(EXIT_FAILURE);
}

static int	ft_strdigit(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0)
			return (-1);
		i++;
	}
	return (0);
}

static void	ft_error(void)
{
	ft_putendl("mlx : initialisation failed");
	exit(EXIT_FAILURE);
}

int			main(int ac, char **av)
{
	t_env		e;

	if (ac != 2 || ft_strdigit(av[1]) == -1 || ft_atoi(av[1]) < 1
		|| ft_atoi(av[1]) > 7)
		ft_usage();
	e.av = av[1];
	if ((e.mlx = mlx_init()) == NULL
		|| (e.win = mlx_new_window(e.mlx, WIDTH, HEIGHT, "RTv1")) == NULL
		|| (e.img = mlx_new_image(e.mlx, WIDTH, HEIGHT)) == NULL)
		ft_error();
	e.data = mlx_get_data_addr(e.img, &e.bpp, &e.line, &e.endian);
	mlx_hook(e.win, 2, (1L << 0), key_p, 0);
	mlx_expose_hook(e.win, expose_hook, &e);
	mlx_loop(e.mlx);
	return (0);
}
