#include <gtk/gtk.h>
#include <string.h>

void yo (GtkWidget *widget, gpointer data)
{
    g_print ("YO %s\n", (char *)data);
}

// static void apply_css (GtkWidget *widget, GtkStyleProvider *provider)
// {
//  gtk_style_context_add_provider (gtk_widget_get_style_context (widget), provider, G_MAXUINT);
//  if (GTK_IS_CONTAINER (widget))
//    gtk_container_forall (GTK_CONTAINER (widget), (GtkCallback) apply_css, provider);
// }

int		main(int ac, char **av)
{
	GtkBuilder		*builder;
	GObject			*window;
	GObject			*button;
	GError			*error;
	GtkCssProvider	*provider;
	GdkDisplay *display;
	GdkScreen *screen;
	// gsize bytes_written, bytes_read;

	gtk_init(&ac, &av);


	// INIT

	builder = gtk_builder_new();
	gtk_builder_add_from_file (builder, "builder.xml", NULL);
	display = gdk_display_get_default ();
	screen = gdk_display_get_default_screen (display);
	provider = gtk_css_provider_new();
	gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
	gtk_css_provider_load_from_path (provider, "gtk.css", &error);

	g_object_unref (provider);
	provider = gtk_css_provider_new();
	gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
	gtk_css_provider_load_from_path (provider, "gtk2.css", &error);


	// SIGNALS

	window = gtk_builder_get_object (builder, "window");
	g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

	button = gtk_builder_get_object (builder, "Sergio");
	g_signal_connect (button, "clicked", G_CALLBACK (yo), "Sergio");

	button = gtk_builder_get_object (builder, "Gordon");
	g_signal_connect (button, "clicked", G_CALLBACK (yo), "Gordon");

	button = gtk_builder_get_object (builder, "quit");
	g_signal_connect (button, "clicked", G_CALLBACK (gtk_main_quit), NULL);

	// apply_css(GTK_WIDGET(window), GTK_STYLE_PROVIDER(provider));

	g_object_unref (provider);
	gtk_main();
	return (0);
}
