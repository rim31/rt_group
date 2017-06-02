/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_area.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/11 15:35:47 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/12 14:45:34 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

gboolean			draw_area(GtkWidget *da, GdkEvent *event, gpointer data)
{
	GdkPixbuf	*pix;
	t_env		*rt;
	cairo_t		*cr;

	(void)event;
	rt = (t_env *)data;
	pix = gdk_pixbuf_new_from_data((const guchar *)rt->data, GDK_COLORSPACE_RGB,
	1, 8, rt->w, rt->h, rt->line, NULL, NULL);
	cr = gdk_cairo_create(gtk_widget_get_window(da));
	gdk_cairo_set_source_pixbuf(cr, pix, 0, 0);
	cairo_paint(cr);
	cairo_destroy(cr);
	return (0);
}
