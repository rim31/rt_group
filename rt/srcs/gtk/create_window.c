/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grass-kw <grass-kw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 14:30:18 by grass-kw          #+#    #+#             */
/*   Updated: 2016/06/12 13:45:59 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static gboolean	expose2(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	t_env *rt;

	(void)widget;
	(void)event;
	rt = (t_env *)data;
	expose(rt);
	gtk_widget_destroy(rt->l_win);
	return (1);
}

void			gtk_setup(t_env *e)
{
	e->win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request(e->win, (int)e->w + 1, (int)e->h + 21);
	gtk_window_set_title(GTK_WINDOW(e->win), "Raytracer");
	gtk_window_set_position(GTK_WINDOW(e->win), GTK_WIN_POS_CENTER);
	gtk_window_set_resizable(GTK_WINDOW(e->win), 0);
	g_signal_connect(e->win, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	e->display = gdk_display_get_default();
	e->screen = gdk_display_get_default_screen(e->display);
	e->provider = gtk_css_provider_new();
	gtk_style_context_add_provider_for_screen(e->screen,
	GTK_STYLE_PROVIDER(e->provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
	gtk_css_provider_load_from_path(e->provider, "srcs/css/gtk.css", &e->error);
	e->l_win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request(e->l_win, 500, 100);
	gtk_window_set_title(GTK_WINDOW(e->l_win), "RAYTRACER");
	gtk_window_set_position(GTK_WINDOW(e->l_win), GTK_WIN_POS_CENTER);
	gtk_window_set_resizable(GTK_WINDOW(e->l_win), 0);
	e->load = gtk_label_new("Please Wait ...");
	gtk_widget_set_name(e->load, "loading");
	gtk_container_add(GTK_CONTAINER(e->l_win), e->load);
	g_signal_connect(e->l_win, "event", G_CALLBACK(expose2), e);
	gtk_widget_show_all(e->l_win);
	gtk_main();
}

void			create_window(char *s)
{
	t_env	rt1;

	global_parser(s, &rt1);
	gtk_setup(&rt1);
}
