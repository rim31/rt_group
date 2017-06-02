/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 11:58:32 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/11 15:54:53 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			response_ok(t_env *rt)
{
	if (rt->filter_color.r != rt->filter_gtk.red * 255
	&& rt->filter_color.g != rt->filter_gtk.green * 255
	&& rt->filter_color.b != rt->filter_gtk.blue * 255)
	{
		rt->i_gtk = 1;
		rt->filter = 1;
		rt->filter_color.r = rt->filter_gtk.red * 255;
		rt->filter_color.g = rt->filter_gtk.green * 255;
		rt->filter_color.b = rt->filter_gtk.blue * 255;
		expose(rt);
		gtk_widget_queue_draw(rt->gtk.box);
		while (gtk_events_pending())
			gtk_main_iteration();
	}
}

static void			choose_color(GtkDialog *dialog, gint response_id,
	gpointer data)
{
	t_env		*rt;

	rt = (t_env *)data;
	gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(dialog), &rt->filter_gtk);
	if (response_id == GTK_RESPONSE_OK)
		response_ok(rt);
	else if (rt->filter)
	{
		rt->i_gtk = 1;
		rt->filter = 0;
		expose(rt);
		gtk_widget_queue_draw(rt->gtk.box);
		while (gtk_events_pending())
			gtk_main_iteration();
	}
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

void				filters_window(GtkWidget *button, gpointer data)
{
	GtkWidget	*dialog;
	t_env		*rt;

	(void)button;
	rt = (t_env *)data;
	dialog = gtk_color_chooser_dialog_new("Filters", GTK_WINDOW(rt->win));
	gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);
	gtk_color_chooser_set_rgba(GTK_COLOR_CHOOSER(dialog), &rt->filter_gtk);
	g_signal_connect(G_OBJECT(dialog), "response", G_CALLBACK(choose_color),
	rt);
	g_signal_connect(G_OBJECT(dialog), "key-press-event", G_CALLBACK(inputs),
	NULL);
	gtk_widget_show_all(dialog);
}
