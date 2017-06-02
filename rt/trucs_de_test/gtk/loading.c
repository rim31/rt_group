/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/04 13:31:00 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/04 14:16:20 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gtk/gtk.h>

static float percent = 0.0;

static gboolean	loading(gpointer data)
{
	percent++;
	if (percent == 1000)
		return 0;
	return 1;
}

int main(int ac, char **av)
{
	GtkWidget	*window;
	GtkWidget	*load;
	GThread		*thread;

	gtk_init(&ac, &av);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 640, 480);
    gtk_window_set_title(GTK_WINDOW(window), "Raytracer");
	gtk_container_set_border_width (GTK_CONTAINER (window), 10);

	// load = gtk_progress_bar_new();
	// gtk_progress_bar_set_show_text(GTK_PROGRESS_BAR(load), TRUE);
	//
	load = gtk_spinner_new ();
	gtk_spinner_start (GTK_SPINNER(load));

	g_timeout_add(300, loading, load);
	gtk_spinner_stop (GTK_SPINNER(load));
	gtk_container_add(GTK_CONTAINER(window), load);

	gtk_widget_show_all(window);
	gtk_main();
	return (0);
}
