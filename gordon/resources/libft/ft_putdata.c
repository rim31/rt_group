/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdata.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grass-kw <grass-kw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/16 09:57:29 by grass-kw          #+#    #+#             */
/*   Updated: 2015/04/16 10:03:35 by grass-kw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putdata(void *data, char const *s, int mode)
{
	ft_putstr(s);
	ft_putstr(" :");
	if (mode == 1)
		ft_putstr((char *)data);
	else if (mode == 2)
		ft_putnbr((int)data);
	ft_putstr(" ");
}
