/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/12 14:41:44 by anonymous         #+#    #+#             */
/*   Updated: 2015/05/12 14:55:11 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strclean(char *s)
{
	if (!s)
		return ;
	else
	{
		ft_strclr(s);
		ft_strdel(&s);
	}
}
