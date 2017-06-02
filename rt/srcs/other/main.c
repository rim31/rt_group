/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 11:08:19 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/07 19:53:40 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		main(int ac, char **av)
{
	if (ac != 2)
		(ac > 2) ? (ft_exit("\033[31mToo many parameters\n")) :
			(ft_exit("\033[31mNot enough parameters\n"));
	if (av[1][ft_strlen(av[1]) - 3] == '.' && av[1][ft_strlen(av[1]) - 2] == 'r'
			&& av[1][ft_strlen(av[1]) - 1] == 't')
	{
		gtk_init(&ac, &av);
		create_window(av[1]);
	}
	else
		ft_exit("\033[31mFiles must have .rt extension\n");
	return (0);
}
