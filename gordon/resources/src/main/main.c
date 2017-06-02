/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grass-kw <grass-kw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/10 06:24:29 by grass-kw          #+#    #+#             */
/*   Updated: 2016/04/22 13:42:20 by grass-kw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_v1.h"

int	main(int ac, char **av)
{
	t_env e;

	if (ac == 2)
	{
		parser(&e, av[1]);
		env_setup(&e);
		draw(&e);
		mlx_key_hook(e.win, key, &e);
		mlx_expose_hook(e.win, expose, &e);
		mlx_loop(e.mlx);
	}
	else
		error();
	return (0);
}
