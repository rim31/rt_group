/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_object.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <oseng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 18:24:02 by oseng             #+#    #+#             */
/*   Updated: 2016/04/20 17:02:33 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** mouvement des objets en fct des coordonnees
** -x : vers nous, + x : vers le fond
** -y : vers la gauche, +y : vers la droite
** -Z : descend,  +z monte
*/

t_env	ft_init_scene(t_env *a, int i)
{
	if (i == 1)
		ft_scene_1(a);
	else if (i == 2)
		ft_scene_2(a);
	else if (i == 3)
		ft_scene_3(a);
	else if (i == 4)
		ft_scene_4(a);
	else if (i == 5)
		ft_scene_5(a);
	else if (i == 6)
		ft_scene_6(a);
	else
		ft_error();
	return (*a);
}
