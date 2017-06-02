#include <gtk/gtk.h>
#include <math.h>

GtkWidget	*window;
GdkRGBA		color;

static void choose_color(GtkDialog *dialog, gint response_id, gpointer user_data)
{
	gtk_color_chooser_get_rgba (GTK_COLOR_CHOOSER (dialog), &color);

	if (response_id == GTK_RESPONSE_OK)
		g_print("%s\n", gdk_rgba_to_string(&color));

  gtk_widget_destroy (GTK_WIDGET (dialog));
}

void	filters_window(GtkWidget *button, gpointer data)
{
	GtkWidget	*dialog;

	dialog = gtk_color_chooser_dialog_new ("Filters", GTK_WINDOW(window));
	gtk_window_set_modal (GTK_WINDOW (dialog), TRUE);
	gtk_color_chooser_set_rgba (GTK_COLOR_CHOOSER (dialog), &color);

	g_signal_connect (G_OBJECT(dialog), "response", G_CALLBACK (choose_color), NULL);

	gtk_widget_show_all(dialog);
}

gchar* format_value_callback (GtkScale *scale, gdouble value)
{
	if (value == 1)
		return g_strdup_printf ("4");
	if (value == 2)
		return g_strdup_printf ("16");
	if (value == 3)
		return g_strdup_printf ("32");
	return g_strdup_printf ("0");
}

void	antialiasing_window(GtkWidget *button, gpointer data)
{
	GtkWidget	*dialog;
	GtkWidget	*scale;
	gint x;
	gint y;

	dialog = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_MOUSE);
    gtk_window_set_default_size(GTK_WINDOW(dialog), 200, 100);
    gtk_window_set_title(GTK_WINDOW(dialog), "Antialiasing");
	gtk_container_set_border_width (GTK_CONTAINER (dialog), 10);
	gtk_window_set_modal (GTK_WINDOW (dialog), TRUE);

	scale = gtk_scale_new_with_range (GTK_ORIENTATION_HORIZONTAL, 0, 3, 2);
	gtk_scale_set_has_origin(GTK_SCALE(scale), 1);
	gtk_scale_add_mark (GTK_SCALE(scale), 0, GTK_POS_BOTTOM, "0");
	gtk_scale_add_mark (GTK_SCALE(scale), 1, GTK_POS_BOTTOM, "4");
	gtk_scale_add_mark (GTK_SCALE(scale), 2, GTK_POS_BOTTOM, "16");
	gtk_scale_add_mark (GTK_SCALE(scale), 3, GTK_POS_BOTTOM, "32");

	g_signal_connect(GTK_SCALE(scale), "format-value", G_CALLBACK(format_value_callback), NULL);

	gtk_container_add(GTK_CONTAINER(dialog), scale);
	gtk_widget_show_all(dialog);
}

void	main_window()
{
	GtkWidget		*box;

	// MENU
	GtkWidget		*menubar;
	GtkWidget		*filemenu;
	GtkWidget		*file;
	GtkWidget		*new;
	GtkWidget		*open;
	GtkWidget		*save;
	GtkWidget		*record;
	GtkWidget		*quit;
	GtkWidget		*antialiasing;
	GtkWidget		*filters;
	GtkWidget		*chooser;

	// CSS
	// GError			*error;
	// GtkCssProvider	*provider;
	// GdkDisplay		*display;
	// GdkScreen		*screen;





	// WINDOW
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 640, 480);
    gtk_window_set_title(GTK_WINDOW(window), "Raytracer");
	gtk_container_set_border_width (GTK_CONTAINER (window), 10);



	// CSS
	// display = gdk_display_get_default ();
	// screen = gdk_display_get_default_screen (display);
	// provider = gtk_css_provider_new ();
	// gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
	// gtk_css_provider_load_from_path (provider, "gtk.css", &error);
	//
	// g_object_unref (provider);



	// MENU
	menubar = gtk_menu_bar_new();

	filemenu = gtk_menu_new();
	file = gtk_menu_item_new_with_label("File");
	new = gtk_menu_item_new_with_label("New");
	open = gtk_menu_item_new_with_label("Open");
	save = gtk_menu_item_new_with_label("Save");
    record = gtk_menu_item_new_with_label("Record");
    quit = gtk_menu_item_new_with_label("Quit");

	gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), filemenu);

	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file);
	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), new);
	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), open);
	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), save);
	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), record);
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), quit);



	filemenu = gtk_menu_new();
	file = gtk_menu_item_new_with_label("Effects");
	antialiasing = gtk_menu_item_new_with_label("Antialiasing");
	filters = gtk_menu_item_new_with_label("Filters");

	gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), filemenu);

	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file);
	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), antialiasing);
	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), filters);



	// BOX
	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(box), menubar, FALSE, FALSE, 3);
	gtk_container_add(GTK_CONTAINER(window), box);


	// SIGNALS
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(G_OBJECT(quit), "activate", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(G_OBJECT(filters), "activate", G_CALLBACK(filters_window), NULL);
	g_signal_connect(G_OBJECT(antialiasing), "activate", G_CALLBACK(antialiasing_window), NULL);



	gtk_widget_show_all(window);
}

int		main(int ac, char **av)
{
	gtk_init(&ac, &av);
	main_window();
	gtk_main();
	return (0);
}
