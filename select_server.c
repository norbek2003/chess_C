#include <gtk/gtk.h>
#include "gui.h"
void process(char *s);
void subserver(int from_client);

int main() {
  int listen_socket;
  int client_socket;
  int subserver_count = 0;
  char buffer[BUFFER_SIZE];
  listen_socket = server_setup();
  while (1) {
    client_socket = server_connect(listen_socket);
    subserver(client_socket);
    break;
  }
}

void subserver(int client_socket) {
  GtkApplication *app;
  GUI_DATA * gui_data = malloc(sizeof(GUI_DATA));
  gui_data->game = generate_game();
  gui_data->selected_piece = NULL;
  gui_data->side = Black;
  gui_data->server_socket = client_socket;

  app = gtk_application_new ("org.gtk.example2", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), gui_data);
  int status = g_application_run (G_APPLICATION (app), 0, NULL);
  g_object_unref (app);
}
