/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 11:58:32 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/03 19:25:46 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

GdkRGBA		color;

static void choose_color(GtkDialog *dialog, gint response_id, gpointer data)
{
	t_env		*rt;

	rt = (t_env *)data;
	gtk_color_chooser_get_rgba (GTK_COLOR_CHOOSER (dialog), &color);

	if (response_id == GTK_RESPONSE_OK)
	{
		if (rt->filter_color.r != color.red * 255
		&& rt->filter_color.g != color.green * 255
		&& rt->filter_color.b != color.blue * 255)
		{
			rt->i_gtk = 1;
			rt->filter = 1;
			rt->filter_color.r = color.red * 255;
			rt->filter_color.g = color.green * 255;
			rt->filter_color.b = color.blue * 255;
			expose(rt);
			gtk_widget_queue_draw (rt->gtk.box);
			while (gtk_events_pending ())
				gtk_main_iteration ();
		}
	}
	else if (rt->filter)
	{
		rt->i_gtk = 1;
		rt->filter = 0;
		expose(rt);
		gtk_widget_queue_draw (rt->gtk.box);
		while (gtk_events_pending ())
			gtk_main_iteration ();
	}
	gtk_widget_destroy (GTK_WIDGET (dialog));
}

void	filters_window(GtkWidget *button, gpointer data)
{
	GtkWidget	*dialog;
	t_env		*rt;

	(void)button;
	rt = (t_env *)data;
	dialog = gtk_color_chooser_dialog_new ("Filters", GTK_WINDOW(rt->win));
	gtk_window_set_modal (GTK_WINDOW (dialog), TRUE);
	gtk_color_chooser_set_rgba (GTK_COLOR_CHOOSER (dialog), &color);

	g_signal_connect (G_OBJECT(dialog), "response", G_CALLBACK (choose_color), rt);

	gtk_widget_show_all(dialog);
}

static gchar* format_value_callback (GtkScale *scale, gdouble value, gpointer data)
{
	t_env *rt;

	(void)scale;
	rt = (t_env *)data;
	if (value == 1)
		rt->antialiasing = 4;
	else if (value == 2)
		rt->antialiasing = 9;
	else
		rt->antialiasing = 0;
	return g_strdup_printf ("%d", rt->antialiasing);
}

static void select_antialiasing (GtkWidget *button, gpointer data)
{
	t_env *rt;

	(void)button;
	rt = (t_env *)data;
	rt->i_gtk = 1;
	expose(rt);
	gtk_widget_queue_draw (rt->gtk.box);
	while (gtk_events_pending ())
		gtk_main_iteration ();
}

static void destroy_dialog (GtkWidget *button, gpointer data)
{
	GtkWidget *dialog;

	(void)button;
	dialog = (GtkWidget *)data;
	gtk_widget_destroy (GTK_WIDGET (dialog));
}

void	antialiasing_window(GtkWidget *button, gpointer data)
{
	GtkWidget	*dialog;
	GtkWidget	*scale;
	GtkWidget	*select;
	GtkWidget	*box;
	t_env		*rt;

	(void)button;
	(void)data;
	rt = (t_env *)data;
	dialog = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_MOUSE);
    gtk_window_set_default_size(GTK_WINDOW(dialog), 200, 100);
    gtk_window_set_title(GTK_WINDOW(dialog), "Antialiasing");
	gtk_container_set_border_width (GTK_CONTAINER (dialog), 10);
	gtk_window_set_modal (GTK_WINDOW (dialog), TRUE);

	scale = gtk_scale_new_with_range (GTK_ORIENTATION_HORIZONTAL, 0, 2, 1);
	gtk_scale_set_has_origin(GTK_SCALE(scale), 1);
	gtk_scale_add_mark (GTK_SCALE(scale), 0, GTK_POS_BOTTOM, "0");
	gtk_scale_add_mark (GTK_SCALE(scale), 1, GTK_POS_BOTTOM, "4");
	gtk_scale_add_mark (GTK_SCALE(scale), 2, GTK_POS_BOTTOM, "9");

	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	select = gtk_button_new_with_label ("Select");

	g_signal_connect(GTK_SCALE(scale), "format-value", G_CALLBACK(format_value_callback), rt);
	g_signal_connect(GTK_BUTTON(select), "clicked", G_CALLBACK(select_antialiasing), rt);
	g_signal_connect(GTK_BUTTON(select), "clicked", G_CALLBACK(destroy_dialog), dialog);

	gtk_box_pack_start(GTK_BOX(box), scale, TRUE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(box), select, TRUE, TRUE, 5);
	gtk_container_add(GTK_CONTAINER(dialog), box);
	gtk_widget_show_all(dialog);
}

gboolean draw_area (GtkWidget *da, GdkEvent *event, gpointer data)
{
    GdkPixbuf *pix;
    t_env *rt;

	(void)event;
    rt = (t_env *)data;
    pix = gdk_pixbuf_new_from_data((const guchar *)rt->data, GDK_COLORSPACE_RGB, 1, 8, rt->w, rt->h, rt->line, NULL, NULL);

    cairo_t *cr;
    cr = gdk_cairo_create (gtk_widget_get_window(da));
    gdk_cairo_set_source_pixbuf(cr, pix, 0, 0);
    cairo_paint(cr);
    cairo_destroy (cr);
	return (0);
}
