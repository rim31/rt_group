/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grass-kw <grass-kw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 13:27:35 by grass-kw          #+#    #+#             */
/*   Updated: 2016/06/11 15:13:29 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	render_threads(t_env *tab_rt, t_env *rt)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < THREADS)
	{
		tab_rt[i] = *rt;
		if (!(tab_rt[i].object = (t_figure *)malloc(sizeof(t_figure)
			* rt->nbobj)))
			ft_exit("\033[31mmalloc of tab_rt in render() failed\n");
		j = 0;
		while (j < rt->nbobj)
		{
			tab_rt[i].object[j] = rt->object[j];
			j++;
		}
		i++;
	}
}

void		render(t_env *rt)
{
	pthread_t	th[THREADS];
	t_env		*tab_rt;
	int			i;
	void		*ret;

	i = 0;
	if (!(tab_rt = (t_env *)malloc(sizeof(t_env) * THREADS)))
		ft_exit("\033[31mmalloc of tab_rt in render() failed\n");
	render_threads(tab_rt, rt);
	while (i < THREADS)
	{
		tab_rt[i].start_h = tab_rt->h * i / THREADS;
		tab_rt[i].end_h = tab_rt->h / THREADS * i + tab_rt->h / THREADS;
		if (pthread_create(&th[i], NULL, raytracer, &tab_rt[i]) != 0)
			ft_exit("\033[31mfailed to create thread");
		i++;
	}
	i = 0;
	while (i < THREADS)
		pthread_join(th[i++], &ret);
}
