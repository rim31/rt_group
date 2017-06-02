/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grass-kw <grass-kw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 14:13:34 by grass-kw          #+#    #+#             */
/*   Updated: 2016/04/22 14:26:20 by grass-kw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_v1.h"

void	parser(t_env *e, char *argument)
{
	ft_bzero(e, sizeof(t_env));
	if (ft_strequ(argument, "scene1"))
		scene1(e);
	else if (ft_strequ(argument, "scene2"))
		scene2(e);
	else if (ft_strequ(argument, "scene3"))
		scene3(e);
	else if (ft_strequ(argument, "scene4"))
		scene4(e);
	else if (ft_strequ(argument, "scene5"))
		scene5(e);
	else if (ft_strequ(argument, "test"))
		test(e);
	else
		error();
}
