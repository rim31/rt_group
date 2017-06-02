/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grass-kw <grass-kw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 13:27:35 by grass-kw          #+#    #+#             */
/*   Updated: 2016/04/29 10:41:30 by grass-kw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	render(t_env *rt)
{
	pthread_t	th[8];
	t_env		tab_rt[8];
	int			i;
	void		*ret;

	i = 0;
	while (i < 8)
		tab_rt[i++] = *rt;
	i = 0;
	while (i < 8)
	{
		tab_rt[i].start_h = 0 + tab_rt->h * i / 8;
		tab_rt[i].end_h = tab_rt->h * (i + 1) / 8;
		if (pthread_create(&th[i], NULL, raytracer, &tab_rt[i]) < 0)
			ft_exit("failed to create thread");
		i++;
	}
	i = 0;
	while (i < 8)
		pthread_join(th[i++], &ret);
}
