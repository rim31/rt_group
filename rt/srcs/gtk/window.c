/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/02 13:14:48 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/12 15:08:58 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

gboolean		animation(gpointer data)
{
	t_env	*rt;
	int		i;

	rt = (t_env *)data;
	if (!rt->animation)
		return (0);
	rt->i_gtk = 1;
	i = 0;
	while (i < rt->nbobj)
	{
		rt->object[i].angle.y += 0.1;
		i++;
	}
	expose(rt);
	gtk_widget_queue_draw(rt->gtk.box);
	while (gtk_events_pending())
		gtk_main_iteration();
	return (1);
}

static gboolean	inputs(GtkWidget *widget, GdkEventKey *event,
	gpointer data)
{
	t_env	*rt;

	(void)widget;
	rt = (t_env *)data;
	if (!ft_strcmp(gdk_keyval_name(event->keyval), "e"))
	{
		if (rt->animation)
			rt->animation = 0;
		else
			rt->animation = 1;
		g_timeout_add(1, animation, rt);
	}
	if (!ft_strcmp(gdk_keyval_name(event->keyval), "Escape"))
		exit(0);
	return (0);
}

static void		destroy_window(GtkWidget *button, gpointer data)
{
	(void)button;
	gtk_widget_destroy(data);
}

static void		create_menu(t_gtk *gtk)
{
	gtk->menubar = gtk_menu_bar_new();
	gtk->filemenu = gtk_menu_new();
	gtk->file = gtk_menu_item_new_with_label("File");
	gtk->open = gtk_menu_item_new_with_label("Open");
	gtk->save = gtk_menu_item_new_with_label("Save");
	gtk->quit = gtk_menu_item_new_with_label("Quit");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(gtk->file), gtk->filemenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(gtk->menubar), gtk->file);
	gtk_menu_shell_append(GTK_MENU_SHELL(gtk->filemenu), gtk->open);
	gtk_menu_shell_append(GTK_MENU_SHELL(gtk->filemenu), gtk->save);
	gtk_menu_shell_append(GTK_MENU_SHELL(gtk->filemenu), gtk->quit);
	gtk->filemenu = gtk_menu_new();
	gtk->file = gtk_menu_item_new_with_label("Effects");
	gtk->antialiasing = gtk_menu_item_new_with_label("Antialiasing");
	gtk->filters = gtk_menu_item_new_with_label("Filters");
	gtk->cartoon = gtk_menu_item_new_with_label("Cartoon");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(gtk->file), gtk->filemenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(gtk->menubar), gtk->file);
	gtk_menu_shell_append(GTK_MENU_SHELL(gtk->filemenu), gtk->antialiasing);
	gtk_menu_shell_append(GTK_MENU_SHELL(gtk->filemenu), gtk->filters);
	gtk_menu_shell_append(GTK_MENU_SHELL(gtk->filemenu), gtk->cartoon);
	gtk->box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start(GTK_BOX(gtk->box), gtk->menubar, FALSE, FALSE, 0);
}

void			gtk(t_env *rt)
{
	t_gtk	*gtk;

	gtk = &rt->gtk;
	create_menu(gtk);
	gtk->area = gtk_drawing_area_new();
	gtk_box_pack_start(GTK_BOX(gtk->box), gtk->area, TRUE, TRUE, 0);
	gtk_container_add(GTK_CONTAINER(rt->win), gtk->box);
	g_signal_connect(G_OBJECT(rt->win), "key-press-event",
	G_CALLBACK(inputs), rt);
	g_signal_connect(G_OBJECT(gtk->save), "activate",
		G_CALLBACK(screenshot), rt);
	g_signal_connect(G_OBJECT(gtk->quit), "activate",
		G_CALLBACK(destroy_window), rt->win);
	g_signal_connect(G_OBJECT(gtk->filters), "activate",
		G_CALLBACK(filters_window), rt);
	g_signal_connect(G_OBJECT(gtk->antialiasing), "activate",
		G_CALLBACK(antialiasing_window), rt);
	g_signal_connect(G_OBJECT(gtk->open), "activate",
		G_CALLBACK(open_file), rt);
	g_signal_connect(G_OBJECT(gtk->cartoon), "activate",
		G_CALLBACK(cartoon_effect), rt);
	g_signal_connect(gtk->area, "draw", G_CALLBACK(draw_area), rt);
	gtk_widget_set_app_paintable(gtk->area, TRUE);
	gtk_widget_show_all(rt->win);
}
