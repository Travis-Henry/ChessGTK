#include <stdio.h>

#include <gtk/gtk.h>

#include "../include/main.h"


//loads the css into the app
void load_css(){
	GtkCssProvider* css_provider = gtk_css_provider_new();
	GFile* css_file = g_file_new_for_path("ui/style.css");

	gtk_css_provider_load_from_file(css_provider, css_file);
		
	
		gtk_style_context_add_provider_for_display(gdk_display_get_default(), GTK_STYLE_PROVIDER(css_provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
	
	g_object_unref(css_provider);
	g_object_unref(css_file);
}

//sets up the app[
static void activate(GtkApplication* app, gpointer userdata){
	GtkBuilder* builder;
	GtkWidget* window;
	GtkStack* stack;
	GtkWidget* menu;


	builder = gtk_builder_new();
	gtk_builder_add_from_file(builder, "ui/window.ui", NULL);
	stack = GTK_STACK(gtk_builder_get_object(builder, "stack"));

	gtk_builder_add_from_file(builder, "ui/menu.ui", NULL);	
	menu = GTK_WIDGET(gtk_builder_get_object(builder, "main_menu"));

	gtk_stack_add_named(stack, menu, "main_menu");

	window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
	gtk_window_set_application(GTK_WINDOW(window), app);	

	load_css();
 	//gtk_window_set_title(GTK_WINDOW(window), "ChessGTK");
    	//gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);


	gtk_window_present(GTK_WINDOW(window));

	g_object_unref(builder);
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
