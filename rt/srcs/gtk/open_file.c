/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/11 15:09:47 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/11 15:10:24 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		file_select(GtkWidget *widget, GtkWidget *dialog)
{
	gchar		*filename;
	GtkWidget	*message;

	filename = (gchar *)gtk_entry_get_text(GTK_ENTRY(widget));
	if (filename[ft_strlen(filename) - 3] == '.'
			&& filename[ft_strlen(filename) - 2] == 'r'
			&& filename[ft_strlen(filename) - 1] == 't'
			&& open(filename, O_RDONLY) != -1)
		create_window(filename);
	else
	{
		if (open(filename, O_RDONLY) != -1)
			message = gtk_message_dialog_new(GTK_WINDOW(dialog),
			GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR,
				GTK_BUTTONS_OK, "Files must have .rt extension");
		else
			message = gtk_message_dialog_new(GTK_WINDOW(dialog),
			GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR,
				GTK_BUTTONS_OK, "This scene doesn't exist");
		gtk_dialog_run(GTK_DIALOG(message));
		gtk_widget_destroy(message);
	}
}

static gboolean	inputs(GtkWidget *widget, GdkEventKey *event, gpointer data)
{
	GtkWidget		*dialog;

	dialog = (GtkWidget *)data;
	if (!ft_strcmp(gdk_keyval_name(event->keyval), "Return"))
		file_select(widget, dialog);
	else if (!ft_strcmp(gdk_keyval_name(event->keyval), "Escape"))
		exit(0);
	return (0);
}

void			open_file(GtkWidget *button, gpointer data)
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
	gtk_container_set_border_width(GTK_CONTAINER(dialog), 10);
	gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);
	select_file = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(select_file), "Choose a file");
	g_signal_connect(G_OBJECT(select_file), "key-press-event",
	G_CALLBACK(inputs), dialog);
	gtk_container_add(GTK_CONTAINER(dialog), select_file);
	gtk_widget_show_all(dialog);
}
