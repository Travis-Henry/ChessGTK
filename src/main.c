#include <stdio.h>

#include <gtk/gtk.h>

#include "../include/main.h"


void build_board(GtkGrid* chessboard);

void on_local_play_clicked(GtkButton* button, gpointer user_data){
	g_print("Test\n");
	GtkBuilder* builder = GTK_BUILDER(user_data);
	GtkStack* stack = GTK_STACK(gtk_builder_get_object(builder, "stack"));
	gtk_stack_set_visible_child_name(stack, "board_screen");
}


//loads the css into the app
void load_css(){
	GtkCssProvider* css_provider = gtk_css_provider_new();
	GFile* css_file = g_file_new_for_path("ui/style.css");

	gtk_css_provider_load_from_file(css_provider, css_file);
	GdkDisplay* display = gdk_display_get_default();
			
	gtk_style_context_add_provider_for_display(display, GTK_STYLE_PROVIDER(css_provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
	
	g_object_unref(css_provider);
	g_object_unref(css_file);
}

//sets up the app[
static void activate(GtkApplication* app, gpointer userdata){
	GtkBuilder* builder;
	GtkWidget* window;
	GtkStack* stack;
	GtkWidget* menu;
	GtkWidget* boardScreen;
	GtkGrid* chessBoard;

	GtkButton* localPlay;

	// Load in the xml files
	builder = gtk_builder_new();
	gtk_builder_add_from_file(builder, "ui/window.ui", NULL);
	gtk_builder_add_from_file(builder, "ui/menu.ui", NULL);	
	gtk_builder_add_from_file(builder, "ui/board.ui", NULL);
	
	// Get needed objects from the builder
	stack = GTK_STACK(gtk_builder_get_object(builder, "stack"));
	menu = GTK_WIDGET(gtk_builder_get_object(builder, "main_menu"));
	boardScreen = GTK_WIDGET(gtk_builder_get_object(builder, "board_screen"));
	chessBoard = GTK_GRID(gtk_builder_get_object(builder, "chess_board"));
	window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
	localPlay = GTK_BUTTON(gtk_builder_get_object(builder, "Local Play"));


	// Add screens to stack view
	gtk_stack_add_named(stack, menu, "main_menu");
	gtk_stack_add_named(stack, boardScreen, "board_screen");

	build_board(chessBoard);
	
	g_signal_connect(localPlay, "clicked", G_CALLBACK(on_local_play_clicked), builder);

	gtk_window_set_application(GTK_WINDOW(window), app);	
 	//gtk_window_set_title(GTK_WINDOW(window), "ChessGTK");
    	//gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
	gtk_window_present(GTK_WINDOW(window));

	//g_object_unref(builder);

	load_css();
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

void build_board(GtkGrid* chessBoard){
	GtkWidget* button;

	gtk_grid_set_row_homogeneous(GTK_GRID(chessBoard), TRUE);
	gtk_grid_set_row_homogeneous(GTK_GRID(chessBoard), TRUE);

	for(int row = 0; row < 8; row++){
		for(int col = 0; col < 8; col++){

			button = gtk_button_new();
			const gchar* class_name = ((row + col) % 2 == 0) ? "white-square" : "black-square";
			gtk_widget_add_css_class(button, class_name);	
			gtk_widget_add_css_class(button, "board-square");


			gchar* id = g_strdup_printf("%d_%d", row, col);
			gtk_widget_set_name(button, id);
			g_free(id);


			gtk_grid_attach(GTK_GRID(chessBoard), button, col, row, 1, 1);
			//TODO add signals

		}
	}

}
