/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grass-kw <grass-kw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 14:30:18 by grass-kw          #+#    #+#             */
/*   Updated: 2016/06/03 20:20:52 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		gtk_setup(t_env *e)
{
	e->win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request (e->win, (int)e->w + 1, (int)e->h + 21);
	gtk_window_set_title(GTK_WINDOW(e->win), "Raytracer");
	gtk_window_set_position(GTK_WINDOW(e->win), GTK_WIN_POS_CENTER);
	gtk_window_set_resizable (GTK_WINDOW(e->win), 0);
    g_signal_connect (e->win, "destroy", G_CALLBACK (gtk_main_quit) , NULL);

	e->display = gdk_display_get_default ();
	e->screen = gdk_display_get_default_screen (e->display);
	e->provider = gtk_css_provider_new();
	gtk_style_context_add_provider_for_screen (e->screen, GTK_STYLE_PROVIDER (e->provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
	gtk_css_provider_load_from_path (e->provider, "srcs/gtk.css", &e->error);

	e->l_win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request (e->l_win, 300, 50);
	gtk_window_set_title(GTK_WINDOW(e->l_win), "Loading");
	gtk_window_set_position(GTK_WINDOW(e->l_win), GTK_WIN_POS_CENTER);
	gtk_window_set_resizable (GTK_WINDOW(e->l_win), 0);
	gtk_window_set_modal (GTK_WINDOW (e->win), TRUE);

	e->load = gtk_progress_bar_new();
	gtk_widget_set_hexpand(e->load, TRUE);
    gtk_widget_set_vexpand(e->load, TRUE);
    gtk_progress_bar_set_show_text(GTK_PROGRESS_BAR(e->load), TRUE);
	gtk_progress_bar_set_pulse_step (GTK_PROGRESS_BAR(e->load), 15);
	gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(e->load), 0.5);
	gtk_progress_bar_set_text (GTK_PROGRESS_BAR(e->load), NULL);
	gtk_progress_bar_pulse (GTK_PROGRESS_BAR(e->load));
	gtk_container_add (GTK_CONTAINER(e->l_win), e->load);
	gtk_widget_show_all(e->l_win);
	g_signal_connect (e->l_win, "destroy", G_CALLBACK (gtk_main_quit) , NULL);
	gtk_main();
}

void	create_window(char *s)
{
	t_env	rt1;

	global_parser(s, &rt1);
	gtk_setup(&rt1);
	if (OPENCL == 1)
		opencl_setup(&rt1.cl, rt1.h, rt1.w);
	// mlx_string_put(rt1.mlx, rt1.win, rt1.w / 2, rt1.h / 2, 0xFFFFFF, "LOADING...");
	// mlx_mouse_hook(rt1.win, my_mouse_funct, &rt1);
	// mlx_hook(rt1.win, 2, (1L << 0), key_press, &rt1);
	// mlx_hook(rt1.win, 3, (1L << 1), key_release, &rt1);
	// mlx_loop_hook(rt1.mlx, expose, &rt1);
	// mlx_loop(rt1.mlx);
	expose(&rt1);
	gtk_main ();
}
