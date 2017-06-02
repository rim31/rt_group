/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grass-kw <grass-kw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 17:22:24 by grass-kw          #+#    #+#             */
/*   Updated: 2016/04/24 17:27:45 by grass-kw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_v1.h"

size_t	ft_lstlen(t_list *lst)
{
	size_t	i;
	t_list	*cursor;

	i = 0;
	cursor = lst;
	while (cursor)
	{
		i++;
		cursor = cursor->next;
	}
	return (i);
}
