/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grass-kw <grass-kw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 14:33:27 by grass-kw          #+#    #+#             */
/*   Updated: 2015/05/11 14:43:37 by grass-kw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_next_line2(int const fd, char **line, t_gnl *e)
{
	static char	buff[BUFF_SIZE + 1];

	*line = ft_strnew(1);
	while (42)
	{
		e->i = 0;
		while (e->ret && buff[e->i] != '\0' && buff[e->i] != '\n')
			e->i++;
		if (e->ret && buff[e->i] == '\n')
		{
			*line = ft_strnjoin(*line, buff, e->i);
			ft_memcpy(buff, buff + e->i + 1, BUFF_SIZE - e->i);
			return (1);
		}
		*line = ft_strjoin(*line, buff);
		ft_bzero(buff, BUFF_SIZE);
		if ((e->ret = read(fd, buff, BUFF_SIZE)))
			buff[BUFF_SIZE] = '\0';
		if (e->ret <= 0)
		{
			if (ft_strequ(buff, ""))
				return ((e->ret == -1 ? e->ret : 0));
			return ((e->ret == -1 ? e->ret : 1));
		}
	}
}

int			get_next_line(int const fd, char **line)
{
	t_gnl e;

	e.i = 0;
	e.ret = 1;
	if (fd < 0 || !line)
		return (-1);
	return (get_next_line2(fd, line, &e));
}
