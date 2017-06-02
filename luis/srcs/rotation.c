/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grass-kw <grass-kw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/11 17:50:25 by lnieto-m          #+#    #+#             */
/*   Updated: 2016/06/06 03:42:57 by grass-kw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vector		derotation(t_vector vision, t_vector angles)
{
	double tmp1;
	double tmp2;

	tmp1 = vision.y;
	tmp2 = vision.z;
	vision.y = tmp1 * cos(-angles.x) - tmp2 * sin(-angles.x);
	vision.z = tmp1 * sin(-angles.x) + tmp2 * cos(-angles.x);
	tmp1 = vision.x;
	tmp2 = vision.z;
	vision.x = tmp1 * cos(-angles.y) + tmp2 * sin(-angles.y);
	vision.z = -tmp1 * sin(-angles.y) + tmp2 * cos(-angles.y);
	tmp1 = vision.x;
	tmp2 = vision.y;
	vision.x = tmp1 * cos(-angles.z) - tmp2 * sin(-angles.z);
	vision.y = tmp1 * sin(-angles.z) + tmp2 * cos(-angles.z);
	return (vision);
}

t_vector		rotation(t_vector vision, t_vector angles)
{
	double tmp1;
	double tmp2;

	tmp1 = vision.y;
	tmp2 = vision.z;
	vision.y = tmp1 * cos(angles.x) - tmp2 * sin(angles.x);
	vision.z = tmp1 * sin(angles.x) + tmp2 * cos(angles.x);
	tmp1 = vision.x;
	tmp2 = vision.z;
	vision.x = tmp1 * cos(angles.y) + tmp2 * sin(angles.y);
	vision.z = -tmp1 * sin(angles.y) + tmp2 * cos(angles.y);
	tmp1 = vision.x;
	tmp2 = vision.y;
	vision.x = tmp1 * cos(angles.z) - tmp2 * sin(angles.z);
	vision.y = tmp1 * sin(angles.z) + tmp2 * cos(angles.z);
	return (vision);
}
