/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_antialiasing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/11 15:41:01 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/11 15:41:31 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

gchar		*format_value_callback(GtkScale *scale, gdouble value,
	gpointer data)
{
	t_env *rt;

	(void)scale;
	rt = (t_env *)data;
	if (value == 1)
		value = 4;
	else if (value == 2)
		value = 16;
	else
		value = 0;
	return (g_strdup_printf("%d", (int)value));
}

void		select_antialiasing(GtkWidget *button, gpointer data)
{
	t_env *rt;

	(void)button;
	rt = (t_env *)data;
	rt->i_gtk = 1;
	expose(rt);
	gtk_widget_queue_draw(rt->gtk.box);
	while (gtk_events_pending())
		gtk_main_iteration();
}

void		refresh_antialiasing(GtkRange *range, gpointer data)
{
	t_env *rt;

	rt = (t_env *)data;
	rt->antialiasing = pow(4, gtk_range_get_value(range));
	if (rt->antialiasing == 1)
		rt->antialiasing = 0;
}
