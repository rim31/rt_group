#include "gtk/gtk.h"

void
delete_event (GtkWidget *widget, GdkEvent *event, gpointer *data)
{
	gtk_main_quit ();
}

/* Construction d'une nouvelle hbox remplie de boutons. Les paramètres qui
 * nous intéressent sont passés à cette fonction.
 * On n'affiche pas la boîte, mais tout ce qu'elle contient. */

GtkWidget *make_box (gint homogeneous, gint spacing,
					gint expand, gint fill, gint padding)
{
	GtkWidget *box;
	GtkWidget *button;
	char padstr[80];

	/* Création d'une hbox avec les paramètres homogeneous et spacing
	 * voulus. */

	box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, spacing);

	/* Création d'une série de boutons configurés de façon appropriée */

	button = gtk_button_new_with_label ("gtk_box_pack");
	gtk_box_pack_start (GTK_BOX (box), button, expand, fill, padding);
	gtk_widget_show (button);

	button = gtk_button_new_with_label ("(box,");
	gtk_box_pack_start (GTK_BOX (box), button, expand, fill, padding);
	gtk_widget_show (button);

	button = gtk_button_new_with_label ("button,");
	gtk_box_pack_start (GTK_BOX (box), button, expand, fill, padding);
	gtk_widget_show (button);

	/* Création d'un bouton portant un label dépendant de la valeur
	 * du paramètre expand. */

	if (expand == TRUE)
			button = gtk_button_new_with_label ("TRUE,");
	else
			button = gtk_button_new_with_label ("FALSE,");

	gtk_box_pack_start (GTK_BOX (box), button, expand, fill, padding);
	gtk_widget_show (button);

	/* Même chose que ci-dessus mais sous forme abrégée. */

	button = gtk_button_new_with_label (fill ? "TRUE," : "FALSE,");
	gtk_box_pack_start (GTK_BOX (box), button, expand, fill, padding);
	gtk_widget_show (button);

	/* Récupération du paramètre padding sous forme de chaîne. */

	sprintf (padstr, "%d);", padding);

	button = gtk_button_new_with_label (padstr);
	gtk_box_pack_start (GTK_BOX (box), button, expand, fill, padding);
	gtk_widget_show (button);

	return box;
}

int main (int argc, char *argv[])
{
	GtkWidget *window;
	GtkWidget *button;
	GtkWidget *box1;
	GtkWidget *box2;
	GtkWidget *separator;
	GtkWidget *label;
	GtkWidget *quitbox;
	int which;

	/* Initialisation, à ne jamais oublier ! :) */

	gtk_init (&argc, &argv);

	if (argc != 2) {
		fprintf (stderr, "usage : %s num, où num vaut 1, 2, ou 3.\n", *argv);

		/* Nettoyage dans GTK et sortie avec un code d'erreur de 1 */
		g_exit (1);
	}

	which = atoi (argv[1]);

	/* Création de notre fenêtre. */

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

	/* Il ne faut jamais oublier de connecter le signal "destroy" à la
	 * fenêtre principale. C'est très important pour disposer d'un
	 * comportement intuitif adéquat. */

	g_signal_connect (G_OBJECT (window), "delete_event",
						G_CALLBACK (delete_event), NULL);

	gtk_window_set_title(GTK_WINDOW(window), "My GTK");
	gtk_window_set_default_size(GTK_WINDOW(window), 640, 480);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);


	/* Création d'une boîte verticale (vbox) pour y placer les boîtes
	 * horizontales.
	 * Ceci permet de placer les boîtes horizontales contenant les boutons
	 * les unes au dessus des autres dans cette vbox. */

	box1 = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);

	/* L'exemple à afficher. Ils correspondent aux images ci-dessus. */

	switch (which) {
	case 1:
		/* Création d'un label. */

		label = gtk_label_new ("gtk_hbox_new (FALSE, 0);");

		/* Alignement du label à gauche.  On précisera cette fonction ainsi
		 * que les autres dans la section sur les attributs des widgets. */

		gtk_misc_set_alignment (GTK_MISC (label), 0, 0);

		/* Placement du label dans la boîte verticale (vbox box1). Il ne
		 * faut pas oublier que les widgets qui s'ajoutent à une vbox sont
		 * placés les uns au dessus des autres. */

		gtk_box_pack_start (GTK_BOX (box1), label, FALSE, FALSE, 0);

		/* Affichage du label */

		gtk_widget_show (label);

		/* On appelle notre fonction de construction de boîte :
		 * homogeneous = FALSE, spacing = 0,
		 * expand = FALSE, fill = FALSE, padding = 0 */

		box2 = make_box (FALSE, 0, FALSE, FALSE, 0);
		gtk_box_pack_start (GTK_BOX (box1), box2, FALSE, FALSE, 0);
		gtk_widget_show (box2);

		/* On appelle notre fonction de construction de boîte :
		 * homogeneous = FALSE, spacing = 0,
		 * expand = TRUE, fill = FALSE, padding = 0 */

		box2 = make_box (FALSE, 0, TRUE, FALSE, 0);
		gtk_box_pack_start (GTK_BOX (box1), box2, FALSE, FALSE, 0);
		gtk_widget_show (box2);

		/* Paramètres : homogeneous = FALSE, spacing = 0,
		 * expand = TRUE, fill = TRUE, padding = 0 */

		box2 = make_box (FALSE, 0, TRUE, TRUE, 0);
		gtk_box_pack_start (GTK_BOX (box1), box2, FALSE, FALSE, 0);
		gtk_widget_show (box2);

		/* Création d'un séparateur, on verra cela plus tard, mais ils sont
		 * simples à utiliser. */

		separator = gtk_hseparator_new ();

		/* Placement du séparateur dans la vbox. Ne pas oublier que tous les
		 * widgets sont placés dans une vbox et qu'il seront placés
		 * verticalement. */

		gtk_box_pack_start (GTK_BOX (box1), separator, FALSE, TRUE, 5);
		gtk_widget_show (separator);

		/* Création d'un nouveau label et affichage de celui-ci. */

		label = gtk_label_new ("gtk_hbox_new (TRUE, 0);");
		gtk_misc_set_alignment (GTK_MISC (label), 0, 0);
		gtk_box_pack_start (GTK_BOX (box1), label, FALSE, FALSE, 0);
		gtk_widget_show (label);

		/* Paramètres : homogeneous = TRUE, spacing = 0,
		 * expand = TRUE, fill = FALSE, padding = 0 */

		box2 = make_box (TRUE, 0, TRUE, FALSE, 0);
		gtk_box_pack_start (GTK_BOX (box1), box2, FALSE, FALSE, 0);
		gtk_widget_show (box2);

		/* Paramètres : homogeneous = TRUE, spacing = 0,
		 * expand = TRUE, fill = TRUE, padding = 0 */

		box2 = make_box (TRUE, 0, TRUE, TRUE, 0);
		gtk_box_pack_start (GTK_BOX (box1), box2, FALSE, FALSE, 0);
		gtk_widget_show (box2);

		/* Un autre séparateur */

		separator = gtk_hseparator_new ();

		/* Les 3 derniers paramètres de gtk_box_pack_start sont :
		 * expand = FALSE, fill = TRUE, padding = 5. */

		gtk_box_pack_start (GTK_BOX (box1), separator, FALSE, TRUE, 5);
		gtk_widget_show (separator);

		break;

	case 2:

		/* Création d'un label, box1 est une vbox identique à
		 * celle créée au début de main() */

		label = gtk_label_new ("gtk_hbox_new (FALSE, 10);");
		gtk_misc_set_alignment (GTK_MISC (label), 0, 0);
		gtk_box_pack_start (GTK_BOX (box1), label, FALSE, FALSE, 0);
		gtk_widget_show (label);

		/* Paramètres : homogeneous = FALSE, spacing = 10,
		 * expand = TRUE, fill = FALSE, padding = 0 */

		box2 = make_box (FALSE, 10, TRUE, FALSE, 0);
		gtk_box_pack_start (GTK_BOX (box1), box2, FALSE, FALSE, 0);
		gtk_widget_show (box2);

		/* Paramètres : homogeneous = FALSE, spacing = 10,
		 * expand = TRUE, fill = TRUE, padding = 0 */

		box2 = make_box (FALSE, 10, TRUE, TRUE, 0);
		gtk_box_pack_start (GTK_BOX (box1), box2, FALSE, FALSE, 0);
		gtk_widget_show (box2);

		separator = gtk_hseparator_new ();

		/* Les 3 derniers paramètres de gtk_box_pack_start sont :
		 * expand = FALSE, fill = TRUE, padding = 5. */

		gtk_box_pack_start (GTK_BOX (box1), separator, FALSE, TRUE, 5);
		gtk_widget_show (separator);

		label = gtk_label_new ("gtk_hbox_new (FALSE, 0);");
		gtk_misc_set_alignment (GTK_MISC (label), 0, 0);
		gtk_box_pack_start (GTK_BOX (box1), label, FALSE, FALSE, 0);
		gtk_widget_show (label);

		/* Paramètres : homogeneous = FALSE, spacing = 0,
		 * expand = TRUE, fill = FALSE, padding = 10 */

		box2 = make_box (FALSE, 0, TRUE, FALSE, 10);
		gtk_box_pack_start (GTK_BOX (box1), box2, FALSE, FALSE, 0);
		gtk_widget_show (box2);

		/* Paramètres : homogeneous = FALSE, spacing = 0,
		 * expand = TRUE, fill = TRUE, padding = 10 */

		box2 = make_box (FALSE, 0, TRUE, TRUE, 10);
		gtk_box_pack_start (GTK_BOX (box1), box2, FALSE, FALSE, 0);
		gtk_widget_show (box2);

		separator = gtk_hseparator_new ();

		/* Les 3 derniers paramètres de gtk_box_pack_start sont :
		 * expand = FALSE, fill = TRUE, padding = 5. */

		gtk_box_pack_start (GTK_BOX (box1), separator, FALSE, TRUE, 5);
		gtk_widget_show (separator);
		break;

	case 3:

		/* Ceci est une démonstration de la possibilité d'utiliser
		 * gtk_box_pack_end() pour aligner les widgets à droite.
		 * On crée d'abord une nouvelle boîte comme d'habitude. */

		box2 = make_box (FALSE, 0, FALSE, FALSE, 0);

		/* On crée le label qui sera mis à la fin. */

		label = gtk_label_new ("end");

		/* On le place en utilisant gtk_box_pack_end(), il est ainsi
		 * mis à droite de la hbox créée par l'appel à make_box(). */

		gtk_box_pack_end (GTK_BOX (box2), label, FALSE, FALSE, 0);

		/* Affichage du label. */

		gtk_widget_show (label);

		/* Placement de box2 dans box1 (la vbox, vous vous rappelez ? :) */

		gtk_box_pack_start (GTK_BOX (box1), box2, FALSE, FALSE, 0);
		gtk_widget_show (box2);

		/* Séparateur pour le bas. */

		separator = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);

		// /* Configuration du séparateur en 400x5 pixels.
		//  * La hbox que l'on a créée aura donc 400 pixels de large,
		//  * et le label "end" sera séparé des autres de la hbox.
		//  * Sinon, tous les widgets de la hbox seraient placés les plus
		//  * près possible les uns des autres. */
		//
		// gtk_widget_set_usize (separator, 400, 5);

		/* Placement du séparateur dans la vbox (box1)
		 * créée au debut de main(). */

		gtk_box_pack_start (GTK_BOX (box1), separator, FALSE, TRUE, 5);
		gtk_widget_show (separator);
	}

	/* Création d'une nouvelle hbox.. vous pouvez en utiliser autant que
	 * que vous en avez besoin ! */

	quitbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);

	/* Notre bouton pour quitter. */

	button = gtk_button_new_with_label ("Quit");

	/* Configuration du signal pour détruire la fenêtre. Ceci enverra le
	 * signal "destroy" à la fenêtre. Ce signal sera à son tour capturé
	 * par notre gestionnaire de signal défini plus haut. */

	g_signal_connect (G_OBJECT (button), "clicked",
							   G_CALLBACK (gtk_widget_destroy),
							   G_OBJECT (window));

	/* Placement du bouton dans la « quitbox ».
	 * Les 3 derniers paramètres de gtk_box_pack_start sont :
	 * expand = TRUE, fill = FALSE, padding = 0. */

	gtk_box_pack_start (GTK_BOX (quitbox), button, TRUE, FALSE, 0);

	/* Placement de la quitbox dans la vbox (box1) */

	gtk_box_pack_start (GTK_BOX (box1), quitbox, FALSE, FALSE, 0);

	/* Placement de la vbox (box1), qui contient maintenant tous nos
	 * widgets, dans la fenêtre principale. */

	gtk_container_add (GTK_CONTAINER (window), box1);

	/* Affichage */

	gtk_widget_show (button);
	gtk_widget_show (quitbox);

	gtk_widget_show (box1);

	/* Affichage de la fenêtre en dernier */

	gtk_widget_show (window);

	/* Ne pas oublier notre fonction principale. */

	gtk_main ();

	/* Le contrôle revient ici lorsque gtk_main_quit() est appelée,
	 * jusqu'à ce que  g_exit() soitutilisée. */

	return 0;
}
