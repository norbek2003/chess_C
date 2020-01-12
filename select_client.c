#include <gtk/gtk.h>
#include "gui.h"


int main(int argc, char ** argv){
  GtkApplication *app;
  GUI_DATA * gui_data = malloc(sizeof(GUI_DATA));
  gui_data->game = generate_game();
  gui_data->selected_piece = NULL;
  gui_data->side = White;
  int server_socket;
  if (argc == 2)
    server_socket = client_setup( argv[1]);
  else
    server_socket = client_setup( TEST_IP );
  
  gui_data->server_socket = server_socket;
  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), gui_data);
  int status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);
}
