/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/04 13:31:00 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/12 14:46:20 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gtk/gtk.h>
#include <stdlib.h>

gboolean draw_area (GtkWidget *da, GdkEvent *event, gpointer data)
{
    GdkPixbuf	*pix;
	const guchar		*data2;

	(void)event;
	data2 = (const guchar *)data;
    pix = gdk_pixbuf_new_from_data(data2, GDK_COLORSPACE_RGB, 0, 8, 2048, 1024, 2048 * 3, NULL, NULL);

    cairo_t *cr;
    cr = gdk_cairo_create (gtk_widget_get_window(da));
    gdk_cairo_set_source_pixbuf(cr, pix, 0, 0);
    cairo_paint(cr);
    cairo_destroy (cr);
	return (0);
}

int main(int ac, char **av)
{
	GtkWidget	*window;
	GdkPixbuf * gbuffer;
    guchar * buffer;
    gsize size;

	gtk_init(&ac, &av);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 640, 480);
    gtk_window_set_title(GTK_WINDOW(window), "Raytracer");
	gtk_container_set_border_width (GTK_CONTAINER (window), 10);

	GtkWidget *area = gtk_drawing_area_new();
	gbuffer = gdk_pixbuf_new_from_file("../../img/earth.jpg", NULL);
	buffer = gdk_pixbuf_get_pixels (gbuffer);

	g_signal_connect(area, "draw", G_CALLBACK(draw_area), buffer);
	gtk_container_add (GTK_CONTAINER(window), area);
	gtk_widget_show_all(window);
	gtk_main();
	return (0);
}
