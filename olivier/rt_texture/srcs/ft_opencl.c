/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opencl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 11:08:05 by lnieto-m          #+#    #+#             */
/*   Updated: 2016/05/20 11:38:03 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ft_opencl(t_env *rt)
{
	int		err;
	size_t	global;

	global = rt->h * rt->w;
	err = clSetKernelArg(rt->cl.kernel, 0, sizeof(cl_mem), &rt->cl.image);
	err = clEnqueueNDRangeKernel(rt->cl.commands, rt->cl.kernel, 1, NULL,
			&global, NULL, 0, NULL, NULL);
	global = rt->h * rt->w;
	err = clEnqueueReadBuffer(rt->cl.commands, rt->cl.image, CL_TRUE, 0,
		sizeof(char) * global, rt->data, 0, NULL, NULL);
}
