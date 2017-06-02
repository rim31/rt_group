/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_key_funct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <oseng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 18:24:02 by oseng             #+#    #+#             */
/*   Updated: 2016/04/22 11:45:14 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_rotation(int keycode, t_env *e)
{
	e->pas = e->pas;
	if (keycode == 53)
	{
		free(e);
		exit(0);
	}
}

int			my_key_funct(int keypress, t_env *a)
{
	if (keypress == 53)
		exit(0);
	if (keypress == 125)
		a->keyup = 1;
	else if (keypress == 126)
		a->keydown = 1;
	if (keypress == 123)
		a->keyleft = 1;
	else if (keypress == 124)
		a->keyrigth = 1;
	if (keypress == 1 || keypress == 49 || keypress == 0)
		ft_rotation(keypress, a);
	ft_bzero((void *)a->data, (H * L * 4) - 1);
	return (0);
}

int			my_keyrelease_funct(int keyrelease, t_env *a)
{
	if (keyrelease == 125)
		a->keyup = 0;
	else if (keyrelease == 126)
		a->keydown = 0;
	if (keyrelease == 123)
		a->keyleft = 0;
	else if (keyrelease == 124)
		a->keyrigth = 0;
	return (0);
}
