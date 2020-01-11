#include <gtk/gtk.h>
#include "chess_base.h"
struct gui_data;
typedef struct{
  int x;
  int y;
  struct gui_data * gui_data;
} POSITION;
typedef struct gui_data{
  GAME * game;
  POSITION * selected_piece;
  GtkWidget * grid[8][8];
} GUI_DATA;

void myCSS(void){
  GtkCssProvider *provider;
  GdkDisplay *display;
  GdkScreen *screen;

  provider = gtk_css_provider_new ();
  display = gdk_display_get_default ();
  screen = gdk_display_get_default_screen (display);
  gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

  const gchar *myCssFile = "gui.css";
  GError *error = 0;

  gtk_css_provider_load_from_file(provider, g_file_new_for_path(myCssFile), &error);
  g_object_unref (provider);
}

void update_board(GUI_DATA * data){
  for(int y = 0; y < 8; y++){
    for(int x = 0; x < 8; x++){
      char * label = calloc(1,1);
      label[0] = (piece_symbol(data->game->board[y][x]));
      gtk_button_set_label(GTK_BUTTON(data->grid[y][x]), label);
      gtk_widget_set_name(data->grid[y][x], (((x + 1) % 2 && (y + 1) % 2) || (x % 2 && y % 2)) ? "black_square" : "white_square");
      if(data->selected_piece && is_valid_move(data->game, data->game->board[data->selected_piece->y][data->selected_piece->x], x, y))
	gtk_widget_set_name(data->grid[y][x], "possible_move");

    }
  }
}

void print_hello (GtkWidget *widget, gpointer data){
  POSITION * p = data;
  POSITION * selected = p->gui_data->selected_piece;
  GAME * game = p->gui_data->game;
  g_print ("Hello World (%d, %d) \n", p->x, p->y);//, data->y);
  if(selected){
    g_print("%d %d %d %d\n", selected->x, selected->y, p->x, p->y);
    if(attempt_piece_move(game, game->board[selected->y][selected->x], p->x, p->y))
      game->turn = !(game->turn);
    p->gui_data->selected_piece = NULL;
  }else{
    p->gui_data->selected_piece = data;
  }
  update_board(p->gui_data);

}

void activate (GtkApplication *app, gpointer gdata){
  GUI_DATA * gui_data = gdata;
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button;
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "CHESS");
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);
  gtk_window_set_default_size (GTK_WINDOW (window), 400, 400);
  myCSS();
  grid = gtk_grid_new ();
  gtk_container_add(GTK_CONTAINER (window), grid);
  for(int y = 0; y < 8; y++){
    for(int x = 0; x < 8; x++){
      button = gtk_button_new_with_label(" ");
      gtk_widget_set_size_request(button, 50, 50);
      POSITION * p = (POSITION*)malloc(sizeof(POSITION));
      p->x = x;
      p->y = y;
      p->gui_data = gui_data;
      g_signal_connect (button, "clicked", G_CALLBACK (print_hello), p);
      gui_data->grid[y][x] = button;
      gtk_grid_attach (GTK_GRID (grid), button, x, 7 - y, 1, 1);
    }
  }
  update_board(gui_data);
  gtk_widget_show_all (window);
}

int main (int argc, char **argv){
  GtkApplication *app;
  int status;
  GUI_DATA * gui_data = malloc(sizeof(GUI_DATA));
  gui_data->game = generate_game();
  gui_data->selected_piece = NULL;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), gui_data);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
