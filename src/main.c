#include <stdio.h>

#include <gtk/gtk.h>

#include "../include/main.h"


static void activate(GtkApplication* app, gpointer userdata){
	GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "ChessGTK");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    gtk_widget_set_visible(window, true);
}


int main(int argc, char* argv[]){

	GtkApplication* app;
	int status = 0;

	app = gtk_application_new("travis.henry.ChessGTK", G_APPLICATION_DEFAULT_FLAGS);	
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);

	return status;
}
