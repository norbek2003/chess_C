#include <gtk/gtk.h>
#include "gui.h"
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
char * piece_symbol_unicode(PIECE * piece){
  if(!piece)
    return " ";
  switch(piece->type){
  case Pawn:
    return "♟";
  case Knight:
    return "♞";
  case Bishop:
    return "♝";
  case Rook:
    return "♜";
  case Queen:
    return "♛";
  case King:
    return "♚";
  }
}
int game_ended_check(GUI_DATA * data, SIDE side){
  if(in_draw(data->game, side)){
    if(in_check(data->game, side)){
      gtk_window_set_title (GTK_WINDOW (data->window), side ? "CHESS! - Black Wins!" : "CHESS! - White Wins!");
    }else{
      gtk_window_set_title (GTK_WINDOW (data->window), "CHESS! - STALEMATE.");
    }
    g_source_remove(data->listener);
    return 1;
   }
  return 0;
}
void update_board(GUI_DATA * data){
  gtk_window_set_title (GTK_WINDOW (data->window), data->game->turn ? "CHESS! - Black To Move" : "CHESS! - White to Move");
  game_ended_check(data, 0);
  game_ended_check(data, 1);
  char * captured[2] = {calloc(64, 1), calloc(64, 1)};
  for(int i = 0; i < 32; i++){
    PIECE * p = data->game->pieces[i];
    if(p->captured)
      strcat(captured[!p->side], piece_symbol_unicode(p));
  }
  for(int i = 0; i < 2; i++)
    gtk_button_set_label(GTK_BUTTON(data->captured_piece_displays[i]), captured[i]);
  for(int y = 0; y < 8; y++){
    for(int x = 0; x < 8; x++){
      PIECE * piece = data->game->board[y][x];
      char * label = calloc(1,1);
      label = piece_symbol_unicode(data->game->board[y][x]);
      gtk_button_set_label(GTK_BUTTON(data->grid[y][x]), label);
      GtkStyleContext *context = gtk_widget_get_style_context(data->grid[y][x]);
      gtk_style_context_remove_class(context,"selected");
      gtk_style_context_remove_class(context,"possible_move");
      gtk_style_context_remove_class(context,"white_piece");
      gtk_style_context_add_class(context,"square");
      gtk_style_context_add_class(context, (((x + 1) % 2 && (y + 1) % 2) || (x % 2 && y % 2)) ? "black_square" : "white_square");
      if(piece && piece->side == White)
	gtk_style_context_add_class(context,"white_piece");
      if(data->selected_piece && data->selected_piece->x == x && data->selected_piece->y == y)
	gtk_style_context_add_class(context,"selected");
      if(data->selected_piece && is_valid_move(data->game, data->game->board[data->selected_piece->y][data->selected_piece->x], x, y))
	gtk_style_context_add_class(context,"possible_move");
    }
  }
}
gboolean listen_for_move(GUI_DATA * data){
  //printf("%d listening %d\n", data->side, data->game->turn);
  char buffer[BUFFER_SIZE];
  if(data->game->turn != data->side && read(data->server_socket, buffer, sizeof(buffer))){
    //printf("Recieving %s\n", buffer);
    buffer[0] -= 65;
    buffer[1] -= 49;
    buffer[2] -= 65;
    buffer[3] -= 49;
    if(attempt_piece_move(data->game, data->game->board[buffer[1]][buffer[0]], buffer[2], buffer[3])){
      data->game->turn = !(data->game->turn);
      update_board(data);
    }
  }else{
    //Filler move to stop the app from freezing on either side
    char b[5] = {65, 49, 65, 49, 0};
    write(data->server_socket, b, sizeof(b));
  }
  return TRUE;
}
void button_press (GtkWidget *widget, gpointer data){
  POSITION * p = data;
  POSITION * selected = p->gui_data->selected_piece;
  GAME * game = p->gui_data->game;
  if(selected){
    if(attempt_piece_move(game, game->board[selected->y][selected->x], p->x, p->y)){
      p->gui_data->selected_piece = NULL;
      update_board(p->gui_data);
      int move[] = {selected->x, selected->y, p->x, p->y, 0};
      char buffer[5];
      move[0] += 65;
      move[1] += 49;
      move[2] += 65;
      move[3] += 49;
      for(int i = 0; i < 4; i++) buffer[i] = move[i];
      update_board(p->gui_data);
      write(p->gui_data->server_socket, buffer, sizeof(buffer));
      //printf("Sending %s\n", buffer);
      game->turn = !(game->turn);
    }
    p->gui_data->selected_piece = NULL;
  }else{
    if(game->turn == p->gui_data->side && game->board[p->y][p->x] && game->board[p->y][p->x]->side == p->gui_data->side)
      p->gui_data->selected_piece = data;
  }
  update_board(p->gui_data);
}
void addEdge(GUI_DATA * data, GtkWidget * grid, int x, int y){
  char * label = calloc(1, 1);
  if(x == y - 1)
    label[0] = ' ';
  else if(x == 0 || x == 9)
    label[0] = (data->side ? "  12345678 " : "  87654321 ")[y];
  else
    label[0] = " ABCDEFGH "[x];
  GtkWidget *button  = gtk_button_new_with_label(label);
  gtk_widget_set_size_request(button, 50, 50);
  gtk_grid_attach (GTK_GRID (grid), button, x, y, 1, 1);
  gtk_style_context_add_class(gtk_widget_get_style_context(button), "edge");

}
void add_captured_piece_displays(GUI_DATA * data, GtkWidget * grid){
  GtkWidget *button  = gtk_button_new_with_label("");
  gtk_widget_set_size_request(button, 50, 50);
  gtk_grid_attach (GTK_GRID (grid), button, 0, 0, 5, 1);
  gtk_style_context_add_class(gtk_widget_get_style_context(button), "square");
  gtk_style_context_add_class(gtk_widget_get_style_context(button), "what_white_captured");
  data->captured_piece_displays[0] = button;
  button  = gtk_button_new_with_label("");
  gtk_widget_set_size_request(button, 50, 50);
  gtk_grid_attach (GTK_GRID (grid), button, 5, 0, 5, 1);
  gtk_style_context_add_class(gtk_widget_get_style_context(button), "square");
  gtk_style_context_add_class(gtk_widget_get_style_context(button), "what_black_captured");
  data->captured_piece_displays[1] = button;
}
void activate (GtkApplication *app, gpointer gdata){
  GUI_DATA * gui_data = gdata;
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button;
  gui_data->listener = g_timeout_add(1000, (GSourceFunc) listen_for_move, (gpointer) gui_data);
  window = gtk_application_window_new (app);
  gui_data->window = window;  
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);
  gtk_window_set_default_size (GTK_WINDOW (window), 500, 500);
  myCSS();
  grid = gtk_grid_new ();
  gtk_container_add(GTK_CONTAINER (window), grid);
  add_captured_piece_displays(gui_data, grid);
  for(int y = 0; y < 8; y++){
    for(int x = 0; x < 8; x++){
      button = gtk_button_new_with_label(" ");
      gtk_widget_set_size_request(button, 50, 50);
      POSITION * p = (POSITION*)malloc(sizeof(POSITION));
      p->x = x;
      p->y = y;
      p->gui_data = gui_data;
      g_signal_connect (button, "clicked", G_CALLBACK (button_press), p);
      gui_data->grid[y][x] = button;
      gtk_grid_attach (GTK_GRID (grid), button, x + 1,  gui_data->side ? y + 2 : 9 - y, 1, 1);
    }
  }

  for(int i = 0; i < 10; i += 1){
    addEdge(gui_data, grid, i, 1);
    addEdge(gui_data, grid, i, 10);
    addEdge(gui_data, grid, 0, i + 1);
    addEdge(gui_data, grid, 9, i + 1);
  }
  update_board(gui_data);
  gtk_widget_show_all (window);
}

