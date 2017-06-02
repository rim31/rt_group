#include <gtk/gtk.h>

void destroy (GtkWidget *widget, gpointer data)
{
    gtk_main_quit ();
}

void yo (GtkWidget *widget, gpointer data)
{
    g_print ("YO %s\n", (char *)data);
}

int		main(int ac, char **av)
{
	GtkWidget *window;
	GtkWidget *button;
	GtkWidget *button2;
	GtkWidget *button3;
	GtkWidget *grid;

	gtk_init(&ac, &av);


	// INIT

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	button = gtk_button_new_with_label ("Sergio");
	button2 = gtk_button_new_with_label ("Gordon");
	button3 = gtk_button_new_with_label ("Olivier");
	grid = gtk_grid_new ();


	// WINDOW

	gtk_window_set_title(GTK_WINDOW(window), "My GTK");
	gtk_window_set_default_size(GTK_WINDOW(window), 640, 480);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);


	// SIGNALS

	g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (destroy), NULL);
	g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (yo), "Sergio");
	g_signal_connect (G_OBJECT (button2), "clicked", G_CALLBACK (yo), "Gordon");
	g_signal_connect (G_OBJECT (button3), "clicked", G_CALLBACK (yo), "Olivier");


	// CONTAINERS

	gtk_container_set_border_width (GTK_CONTAINER (window), 320);
	gtk_container_add (GTK_CONTAINER (window), grid);
	gtk_grid_attach(GTK_GRID(grid), button, 0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), button2, 1, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), button3, 0, 1, 2, 1);


	// WIDGET SHOW

	gtk_widget_show_all(window);

	gtk_main();
	return (0);
}
