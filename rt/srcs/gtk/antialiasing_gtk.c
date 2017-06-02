/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing_gtk.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/11 15:36:24 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/11 15:48:09 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			destroy_dialog(GtkWidget *button, gpointer data)
{
	GtkWidget *dialog;

	(void)button;
	dialog = (GtkWidget *)data;
	gtk_widget_destroy(GTK_WIDGET(dialog));
}

static gboolean		inputs(GtkWidget *widget, GdkEventKey *event,
	gpointer data)
{
	(void)widget;
	(void)data;
	if (!ft_strcmp(gdk_keyval_name(event->keyval), "Escape"))
		exit(0);
	return (0);
}

static void			init_window(GtkWidget **dialog, GtkWidget **scale,
	GtkWidget **select, GtkWidget **box)
{
	*dialog = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(*dialog), GTK_WIN_POS_MOUSE);
	gtk_window_set_default_size(GTK_WINDOW(*dialog), 200, 100);
	gtk_window_set_title(GTK_WINDOW(*dialog), "Antialiasing");
	gtk_container_set_border_width(GTK_CONTAINER(*dialog), 10);
	gtk_window_set_modal(GTK_WINDOW(*dialog), TRUE);
	*scale = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0, 2, 2);
	gtk_scale_set_has_origin(GTK_SCALE(*scale), 1);
	gtk_scale_add_mark(GTK_SCALE(*scale), 0, GTK_POS_BOTTOM, "0");
	gtk_scale_add_mark(GTK_SCALE(*scale), 1, GTK_POS_BOTTOM, "4");
	gtk_scale_add_mark(GTK_SCALE(*scale), 2, GTK_POS_BOTTOM, "16");
	*box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	*select = gtk_button_new_with_label("Select");
}

void				antialiasing_window(GtkWidget *button, gpointer data)
{
	GtkWidget	*dialog;
	GtkWidget	*scale;
	GtkWidget	*select;
	GtkWidget	*box;
	t_env		*rt;

	(void)button;
	rt = (t_env *)data;
	rt->antialiasing = 0;
	init_window(&dialog, &scale, &select, &box);
	g_signal_connect(GTK_RANGE(scale), "value-changed",
		G_CALLBACK(refresh_antialiasing), rt);
	g_signal_connect(GTK_SCALE(scale), "format-value",
		G_CALLBACK(format_value_callback), rt);
	g_signal_connect(GTK_BUTTON(select), "clicked",
		G_CALLBACK(select_antialiasing), rt);
	g_signal_connect(GTK_BUTTON(select), "clicked",
		G_CALLBACK(destroy_dialog), dialog);
	g_signal_connect(G_OBJECT(dialog), "key-press-event",
		G_CALLBACK(inputs), NULL);
	gtk_box_pack_start(GTK_BOX(box), scale, TRUE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(box), select, TRUE, TRUE, 5);
	gtk_container_add(GTK_CONTAINER(dialog), box);
	gtk_widget_show_all(dialog);
}
