/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grass-kw <grass-kw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/16 17:07:53 by grass-kw          #+#    #+#             */
/*   Updated: 2015/04/16 17:12:35 by grass-kw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
*** Print array type **char
*/

void	ft_put_array(char **tab)
{
	int	i;

	i = 0;
	ft_putendl("array(");
	while (tab[i])
	{
		ft_putstr("\t");
		ft_putnbr(i);
		ft_putstr(" => ");
		ft_putendl(tab[i]);
		i++;
	}
}
