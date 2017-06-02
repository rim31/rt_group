/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 11:56:33 by lnieto-m          #+#    #+#             */
/*   Updated: 2016/05/18 14:57:24 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int		result;
	int		index;
	int		tmp;

	result = 0;
	index = 0;
	tmp = index;
	while (str[index] == '\t' || str[index] == ' ' || str[index] == '\n'
			|| str[index] == '\r' || str[index] == '\f' || str[index] == '\v')
		index++;
	if (str[index] == '-' || str[index] == '+')
	{
		tmp = index;
		index++;
	}
	while (str[index])
	{
		result *= 10;
		result += str[index] - 48;
		index++;
	}
	if (str[tmp] == '-')
		result *= -1;
	return (result);
}
