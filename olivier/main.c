/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <oseng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 18:24:02 by oseng             #+#    #+#             */
/*   Updated: 2016/04/22 12:26:55 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_env	ft_init(t_env *a, int i)
{
	a->x = 0;
	a->y = 0;
	a->pas = 30;
	a->xx = 0;
	a->yy = 0;
	a->k0 = 1000000;
	a->k = 10000000;
	a->keyup = 0;
	a->keydown = 0;
	a->keyleft = 0;
	a->keyrigth = 0;
	a->nblum = 1;
	ft_init_scene(a, i);
	return (*a);
}

/*
** need a parser per haps
*/

int				main(int argc, char **argv)
{
	t_env		*a;

	ft_putstr("\033[92mEnter the number of scene : 1 <-> 6\n\033[0m");
	if (argc == 2)
	{
		a = malloc(sizeof(t_env));
		if (ft_atoi(argv[1]) >= 1 && ft_atoi(argv[1]) <= 7)
		{
			ft_putstr("\033[92mBONUS: multi ligths, brigthness\n\033[0m");
			*a = ft_init(a, ft_atoi(argv[1]));
			ft_start_screen(*a);
		}
		else
			ft_putstr("\033[96mERROR :-P\n\033[0m");
		free(a);
	}
	ft_putstr("\033[96m1 : cylindre + plan\n\033[0m");
	ft_putstr("\033[96m2 : sphere\n\033[0m");
	ft_putstr("\033[96m3 : cylindre\n\033[0m");
	ft_putstr("\033[96m4 : cone + cylindre + sphere + 2 plans\n\033[0m");
	ft_putstr("\033[96m5 : rotation scene 4\n\033[0m");
	ft_putstr("\033[96m6 : colonnes + spheres + plans\n\033[0m");
	ft_putstr("\033[96m7 : mulitspot + spheres + plans\n\033[0m");
	return (0);
}

t_vect			ft_tmp(t_vect vect)
{
	t_vect		tmp;

	tmp.x = vect.x;
	tmp.y = vect.y;
	tmp.z = vect.z;
	return (tmp);
}
