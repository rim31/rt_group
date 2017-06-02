/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cartoon.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/11 15:11:33 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/11 15:39:21 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static gboolean	inputs(GtkWidget *widget, GdkEventKey *event,
	gpointer data)
{
	(void)widget;
	(void)data;
	if (!ft_strcmp(gdk_keyval_name(event->keyval), "Escape"))
		exit(0);
	return (0);
}

static gboolean	switch_active(GtkSwitch *widget, gboolean state, gpointer data)
{
	t_env *rt;

	(void)widget;
	rt = (t_env *)data;
	rt->i_gtk = 1;
	if (state)
	{
		rt->cel_shading = 1;
		expose(rt);
		gtk_widget_queue_draw(rt->gtk.box);
		while (gtk_events_pending())
			gtk_main_iteration();
		return (1);
	}
	else
	{
		rt->cel_shading = 0;
		expose(rt);
		gtk_widget_queue_draw(rt->gtk.box);
		while (gtk_events_pending())
			gtk_main_iteration();
		return (0);
	}
}

void			cartoon_effect(GtkWidget *button, gpointer data)
{
	GtkWidget	*dialog;
	GtkWidget	*yes_no;
	t_env		*rt;

	(void)button;
	rt = (t_env *)data;
	dialog = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_MOUSE);
	gtk_window_set_default_size(GTK_WINDOW(dialog), 200, 50);
	gtk_window_set_title(GTK_WINDOW(dialog), "Cartoon Effect");
	gtk_container_set_border_width(GTK_CONTAINER(dialog), 10);
	gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);
	yes_no = gtk_switch_new();
	(rt->cel_shading) ? (gtk_switch_set_active(GTK_SWITCH(yes_no), TRUE)) :
		(gtk_switch_set_active(GTK_SWITCH(yes_no), FALSE));
	g_signal_connect(GTK_SWITCH(yes_no), "state-set",
		G_CALLBACK(switch_active), rt);
	g_signal_connect(GTK_SWITCH(yes_no), "key-press-event",
		G_CALLBACK(inputs), NULL);
	gtk_container_add(GTK_CONTAINER(dialog), yes_no);
	gtk_widget_show_all(dialog);
}
