/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/11 15:14:51 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/11 15:38:16 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		save_file(GtkWidget *widget, t_env *rt)
{
	cairo_surface_t *surface;

	surface = cairo_image_surface_create_for_data((unsigned char *)rt->tmp_data,
	CAIRO_FORMAT_ARGB32, rt->w, rt->h,
	cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, rt->w));
	cairo_surface_write_to_png(surface, gtk_entry_get_text(GTK_ENTRY(widget)));
	gtk_widget_destroy(rt->dialog);
}

static gboolean	inputs(GtkWidget *widget, GdkEventKey *event,
	gpointer data)
{
	t_env *rt;

	rt = (t_env *)data;
	if (!ft_strcmp(gdk_keyval_name(event->keyval), "Return"))
		save_file(widget, rt);
	else if (!ft_strcmp(gdk_keyval_name(event->keyval), "Escape"))
		exit(0);
	return (0);
}

static void		create_data(t_env *rt)
{
	int				i;

	if (!(rt->tmp_data = (unsigned char *)malloc(sizeof(unsigned char) *
	rt->w * rt->h * 4)))
		ft_exit("\033[31mMalloc of tmp in screenshot() failed\n");
	i = 0;
	while (i < rt->w * rt->h * 4)
	{
		rt->tmp_data[i] = rt->data[i + 2];
		rt->tmp_data[i + 1] = rt->data[i + 1];
		rt->tmp_data[i + 2] = rt->data[i];
		rt->tmp_data[i + 3] = rt->data[i + 3];
		i += 4;
	}
}

void			screenshot(GtkWidget *button, gpointer data)
{
	t_env			*rt;
	GtkWidget		*select_file;

	(void)button;
	rt = (t_env *)data;
	create_data(rt);
	rt->dialog = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(rt->dialog), GTK_WIN_POS_MOUSE);
	gtk_window_set_default_size(GTK_WINDOW(rt->dialog), 200, 50);
	gtk_window_set_title(GTK_WINDOW(rt->dialog), "Save");
	gtk_container_set_border_width(GTK_CONTAINER(rt->dialog), 10);
	gtk_window_set_modal(GTK_WINDOW(rt->dialog), TRUE);
	select_file = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(select_file),
	"Choose a file name");
	g_signal_connect(G_OBJECT(select_file), "key-press-event",
	G_CALLBACK(inputs), rt);
	gtk_container_add(GTK_CONTAINER(rt->dialog), select_file);
	gtk_widget_show_all(rt->dialog);
}
