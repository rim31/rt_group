#include <gtk/gtk.h>


int main(int ac, char **av)
{
	GtkWidget *parent_window;

	gtk_init(&ac, &av);
	parent_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(parent_window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(parent_window), 640, 480);
    gtk_window_set_title(GTK_WINDOW(parent_window), "Raytracer");
	gtk_container_set_border_width (GTK_CONTAINER (parent_window), 10);

	GtkWidget *dialog;
GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
gint res;

dialog = gtk_file_chooser_dialog_new ("Open File",
                                      GTK_WINDOW(parent_window),
                                      action,
                                      ("Cancel"),
                                      GTK_RESPONSE_CANCEL,
                                      ("Open"),
                                      GTK_RESPONSE_ACCEPT,
                                      NULL);

  res = gtk_dialog_run (GTK_DIALOG (dialog));
  if (res == GTK_RESPONSE_ACCEPT)
    {
      char *filename;
      GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
      filename = gtk_file_chooser_get_filename (chooser);
      g_free (filename);
    }

	gtk_widget_show_all(parent_window);
	gtk_main();
	return (0);
}
