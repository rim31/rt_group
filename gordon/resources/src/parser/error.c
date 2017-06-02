/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grass-kw <grass-kw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/22 10:14:00 by grass-kw          #+#    #+#             */
/*   Updated: 2016/04/22 12:31:59 by grass-kw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_v1.h"

void	error(void)
{
	ft_putstr("wrong format\t(ex : rt_v1 scene1)\tall scene : scene1 scene2 ");
	ft_putendl("scene3 scene4 scene5");
}
