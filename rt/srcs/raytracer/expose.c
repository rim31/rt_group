/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/20 14:30:36 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/11 14:41:41 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		expose(t_env *rt)
{
	rt->bpp = 32;
	rt->line = rt->w * 4;
	if (!(rt->data = (char *)malloc(sizeof(char) * (rt->w * rt->h * 4))))
		ft_exit("\033[31mmalloc of rt->data in expose() failed\n");
	render(rt);
	if (!rt->i_gtk)
		gtk(rt);
	return (0);
}
