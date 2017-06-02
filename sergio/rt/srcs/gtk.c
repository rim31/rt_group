/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/02 13:14:48 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/03 20:06:36 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static gboolean escape(GtkWidget *widget, GdkEventKey *event)
{
	(void)widget;
    if (!ft_strcmp(gdk_keyval_name(event->keyval), "Escape"))
		gtk_main_quit();
    return (0);
}

static void		file_select(GtkWidget *widget, GtkWidget *dialog)
{
	gchar		*filename;
	GtkWidget	*message;

	filename = (gchar *)gtk_entry_get_text (GTK_ENTRY(widget));
	if (filename[ft_strlen(filename) - 3] == '.'
			&& filename[ft_strlen(filename) - 2] == 'r'
			&& filename[ft_strlen(filename) - 1] == 't' && open(filename, O_RDONLY) != -1)
		create_window(filename);
	else
	{
		if (open(filename, O_RDONLY) != -1)
			message = gtk_message_dialog_new(GTK_WINDOW(dialog), GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR,
				GTK_BUTTONS_OK, "Files must have .rt extension");
		else
			message = gtk_message_dialog_new(GTK_WINDOW(dialog), GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR,
				GTK_BUTTONS_OK, "This scene doesn't exist");
		gtk_dialog_run (GTK_DIALOG (message));
		gtk_widget_destroy (message);
	}
}

static gboolean enter(GtkWidget *widget, GdkEventKey *event, gpointer data)
{
	GtkWidget		*dialog;

	dialog = (GtkWidget *)data;
    if (!ft_strcmp(gdk_keyval_name(event->keyval), "Return"))
		file_select(widget, dialog);
    return (0);
}

static void		open_file(GtkWidget *button, gpointer data)
{
	GtkWidget		*select_file;
	GtkWidget		*dialog;
	t_env			*rt;

	(void)button;
	rt = (t_env *)data;
	dialog = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_MOUSE);
    gtk_window_set_default_size(GTK_WINDOW(dialog), 200, 50);
    gtk_window_set_title(GTK_WINDOW(dialog), "Open");
	gtk_container_set_border_width (GTK_CONTAINER (dialog), 10);
	gtk_window_set_modal (GTK_WINDOW (dialog), TRUE);
	select_file = gtk_entry_new();
	gtk_entry_set_placeholder_text (GTK_ENTRY(select_file), "Choose a file");

	g_signal_connect(G_OBJECT(select_file), "key-press-event", G_CALLBACK(enter), dialog);
	gtk_container_add (GTK_CONTAINER(dialog), select_file);
	gtk_widget_show_all(dialog);
}

void	gtk(t_env *rt)
{
	t_gtk	*gtk;

	gtk = &rt->gtk;
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

	gtk_menu_item_set_submenu(GTK_MENU_ITEM(gtk->file), gtk->filemenu);

	gtk_menu_shell_append(GTK_MENU_SHELL(gtk->menubar), gtk->file);
	gtk_menu_shell_append(GTK_MENU_SHELL(gtk->filemenu), gtk->antialiasing);
	gtk_menu_shell_append(GTK_MENU_SHELL(gtk->filemenu), gtk->filters);



	gtk->box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start(GTK_BOX(gtk->box), gtk->menubar, FALSE, FALSE, 0);

	gtk->area = gtk_drawing_area_new();
    gtk_box_pack_start(GTK_BOX(gtk->box), gtk->area, TRUE, TRUE, 0);


	gtk_container_add (GTK_CONTAINER(rt->win), gtk->box);

	g_signal_connect(G_OBJECT(rt->win), "key-press-event", G_CALLBACK(escape), NULL);

	g_signal_connect(G_OBJECT(gtk->quit), "activate", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(G_OBJECT(gtk->filters), "activate", G_CALLBACK(filters_window), rt);
	g_signal_connect(G_OBJECT(gtk->antialiasing), "activate", G_CALLBACK(antialiasing_window), rt);
	g_signal_connect(G_OBJECT(gtk->open), "activate", G_CALLBACK(open_file), rt);
    g_signal_connect(gtk->area, "draw", G_CALLBACK(draw_area), rt);

    gtk_widget_set_app_paintable(gtk->area, TRUE);
    gtk_widget_show_all(rt->win);
}
